#include <stdio.h>
#include <stdlib.h>

#include "PriorityQueue.h"
#include "FIFOQueue.h"
#include "Event.h"


int SEED;   //Seed for random number generation
int INIT_TIME;  //Initial time the simulation starts
int FIN_TIME;   //The time the simulation ends
int EQ_CAPACITY;    //Capacity of the event queue
int CPU_CAPACITY;   //Capacity of the CPU queue
int DISK_CAPACITY;  //Capacity of the disks queues
int ARRIVE_MIN; //Minimum amount of time for job to arrive
int ARRIVE_MAX; //Maximum amount time for job to arrive
int CPU_MIN;    //Minimum amount of time it takes to finish CPU event
int CPU_MAX;   //Maximum amount of time it takes to finish CPU event
int DISK1_MIN;  //Minimum amount of time it takes to finish Disk1 event
int DISK1_MAX; //Maximum amount of time it takes to finish Disk1 event
int DISK2_MIN;  //Minimum amount of time it takes to finish Disk2 event
int DISK2_MAX; //Maximum amount of time it takes to finish Disk2 event
double QUIT_PROB;   //Probability an event quits after being processed at CPU

int randGen(int min, int max);

/*
    Main loop of the simulator. Runs from INIT_TIME to FIN_TIME
*/
int main(){
    FILE *config = fopen("config.txt", "r");
    if(config != NULL){
        fscanf(config, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %lf", &SEED, &INIT_TIME, &FIN_TIME, &EQ_CAPACITY, &CPU_CAPACITY,
               &DISK_CAPACITY, &ARRIVE_MIN, &ARRIVE_MAX, &CPU_MIN, &CPU_MAX, &DISK1_MIN, &DISK1_MAX, &DISK2_MIN, &DISK2_MAX, &QUIT_PROB);
    }
    else{
        printf("Error, file couldn't be opened");
    }
    fclose(config);

    FILE *log = fopen("log.log", "w");
    fprintf(log, "Value of Constants");
    fprintf(log, "\nSEED: %d", SEED);
    fprintf(log, "\nINIT_TIME: %d", INIT_TIME);
    fprintf(log, "\nFIN_TIME: %d", FIN_TIME);
    fprintf(log, "\nEQ_CAPACITY: %d", EQ_CAPACITY);
    fprintf(log, "\nCPU_CAPACITY: %d", CPU_CAPACITY);
    fprintf(log, "\nDISK_CAPACITY: %d", DISK_CAPACITY);
    fprintf(log, "\nARRIVE_MIN: %d", ARRIVE_MIN);
    fprintf(log, "\nARRIVE_MAX: %d", ARRIVE_MAX);
    fprintf(log, "\nCPU_MIN: %d", CPU_MIN);
    fprintf(log, "\nCPU_MAX: %d", CPU_MAX);
    fprintf(log, "\nDISK1_MIN: %d", DISK1_MIN);
    fprintf(log, "\nDISK1_MAX: %d", DISK1_MAX);
    fprintf(log, "\nDISK2_MIN: %d", DISK2_MIN);
    fprintf(log, "\nDISK2_MAX: %d", DISK2_MAX);
    fprintf(log, "\nDISK2_MIN: %lf\n", QUIT_PROB);

    //Initialize variables
    int runTime = INIT_TIME;
    int jobId = 1;
    Event currentJob;
    srand(SEED);

    int cpuBusy = 0;
    int diskOneBusy = 0;
    int diskTwoBusy = 0;
    int finishingTime = 0;
    Event processingEvent;

    //Initialize queues
    PriorityQueue *eventQueue = initalizeEQ(EQ_CAPACITY);
    FIFOQueue *cpuQueue = initialize(CPU_CAPACITY);
    FIFOQueue *disk1 = initialize(DISK_CAPACITY);
    FIFOQueue *disk2 = initialize(DISK_CAPACITY);

    //Statistic variables
    int eqMax = 0;
    int eqTotal = 0;
    int cpuMax = 0;
    int cpuTotal = 0;
    int disk1Max = 0;
    int disk1Total = 0;
    int disk2Max = 0;
    int disk2Total = 0;
    int numOfRuns = 0;
    int cpuBusyTime = 0;
    int disk1BusyTime = 0;
    int disk2BusyTime = 0;
    int cpuResponseTotal = 0;
    int cpuResponseMax = 0;
    int disk1ResponseTotal = 0;
    int disk1ResponseMax = 0;
    int disk2ResponseTotal = 0;
    int disk2ResponseMax = 0;
    int cpuCompleted = 0;
    int disk1Completed = 0;
    int disk2Completed = 0;

    //Insert initial events
    eventQInsert(eventQueue, createEvent(0, 0, INIT_TIME));
    eventQInsert(eventQueue, createEvent(0, 1, FIN_TIME));
    eventQInsert(eventQueue, createEvent(jobId, 2, INIT_TIME));

    fprintf(log, "\nEvent Log");
    //Event handler (main loop of simulator)
    //Runs as long as event queue isn't empty and the end time is not reached
    while(!isEmpty(eventQueue) && runTime < FIN_TIME){
        //Pop's next job of priority queue
        currentJob = popMin(eventQueue);
        fprintf(log,"\n");
        if(currentJob.type == 0){
            fprintf(log, "SIM_START at %d", currentJob.time);
            //event
        }
        else if(currentJob.type == 1){
            fprintf(log, "SIM_END at %d", currentJob.time);
            //event
        }
        else{
            fprintf(log, "At time %d ", currentJob.time);
            fprintf(log, "job%d ", currentJob.id);
            if(currentJob.type == 2){
                fprintf(log, "arrives at CPU.");
            }
            else if(currentJob.type == 3){
                fprintf(log, "finishes at CPU.");
            }
            else if(currentJob.type == 4){
                fprintf(log, "arrives at disk1.");
            }
            else if(currentJob.type == 5){
                fprintf(log, "finishes at disk1.");
            }
            else if(currentJob.type == 6){
                fprintf(log, "arrives at disk2.");
            }
            else if(currentJob.type == 7){
                fprintf(log, "finishes at disk2.");
            }
            else if(currentJob.type == 8){
                fprintf(log, "exits.");
            }
        }
        //update runtime to current job's time
        runTime = currentJob.time;

        //select type of current job and handle event
        switch(currentJob.type){
            case 0: break;  //SIM_START, do nothing
            case 1: break;  //SIM_END, do nothing
            //Arrival, processCPU(currentJob)
            case 2: //CPU ARRIVAL
                    //Create new arrival event and insert into event queue
                    jobId++;
                    eventQInsert(eventQueue, createEvent(jobId, 2, runTime + randGen(ARRIVE_MIN, ARRIVE_MAX)));
                    //Send current event to CPU FIFO
                    insertFIFO(cpuQueue, currentJob);
                    break;
            case 3: //CPU FINISH
                    //Set CPU to idle
                    cpuBusy = 0;
                    cpuCompleted++;

                    //Probability that current event exits after CPU
                    if(randGen(0,100) <= (int)(QUIT_PROB * 100)){
                        eventQInsert(eventQueue, createEvent(currentJob.id, 8, currentJob.time));   //Create exit event
                    }
                    else{
                        //Event leaves CPU, decide which disk to send to
                        if(disk1->rear == disk2->rear){
                            int randNum = randGen(0,100);
                            if(randNum <= 50){
                                eventQInsert(eventQueue, createEvent(currentJob.id, 4, currentJob.time));
                            }
                            else{
                                eventQInsert(eventQueue, createEvent(currentJob.id, 6, currentJob.time));
                            }
                        }
                        else if(disk1->rear < disk2->rear){
                            eventQInsert(eventQueue, createEvent(currentJob.id, 4, currentJob.time));
                        }
                        else{
                            eventQInsert(eventQueue, createEvent(currentJob.id, 6, currentJob.time));
                        }
                    }
                    break;  //Finish, processCPU(currentJob)
            case 4: //DISK ARRIVE
                    insertFIFO(disk1, currentJob);
                    break;
            case 5: //DISK FINISH
                    //Find which disk event is in, set that disk to idle
                    diskOneBusy = 0;
                    disk1Completed++;
                    //Send event to arrive at CPU
                    eventQInsert(eventQueue, createEvent(currentJob.id, 2, currentJob.time));
                    break;
            case 6: //DISK2 ARRIVE
                    insertFIFO(disk2, currentJob);
                    break;
            case 7: //DISK2 FINISH
                    diskTwoBusy = 0;
                    disk2Completed++;
                    //Send event to arrive at CPU
                    eventQInsert(eventQueue, createEvent(currentJob.id, 2, currentJob.time));
                    break;
            case 8: //JOB EXITS
                    break;
        }

        //CPU processing
        if(!cpuBusy && !isEmptyFIFO(cpuQueue)){
            //Pop next event from FIFO
            processingEvent = removeFIFO(cpuQueue);
            //Determine finishing time
            finishingTime = runTime + randGen(CPU_MIN, CPU_MAX);
            //Create finishing event
            eventQInsert(eventQueue, createEvent(processingEvent.id, 3, finishingTime));
            //Set CPU to busy
            cpuBusy = 1;

            cpuBusyTime = cpuBusyTime + finishingTime;

            cpuResponseTotal = cpuResponseTotal + (finishingTime - processingEvent.time);

            if(finishingTime - processingEvent.time > cpuResponseMax){
                cpuResponseMax = finishingTime - processingEvent.time;
            }
        }

        //Disk1 processing
        if(!diskOneBusy && !isEmptyFIFO(disk1)){
            processingEvent = removeFIFO(disk1);
            finishingTime = runTime + randGen(DISK1_MIN, DISK1_MAX);
            eventQInsert(eventQueue, createEvent(processingEvent.id, 5, finishingTime));
            diskOneBusy = 1;

            disk1BusyTime = disk1BusyTime + finishingTime;

            disk1ResponseTotal = disk1ResponseTotal + (finishingTime - processingEvent.time);

            if(finishingTime - processingEvent.time > disk1ResponseMax){
                disk1ResponseMax = finishingTime - processingEvent.time;
            }
        }

        //Disk2 processing
        if(!diskTwoBusy && !isEmptyFIFO(disk2)){
            processingEvent = removeFIFO(disk2);
            finishingTime = runTime + randGen(DISK2_MIN, DISK2_MAX);
            eventQInsert(eventQueue, createEvent(processingEvent.id, 7, finishingTime));
            diskTwoBusy = 1;

            disk2BusyTime = disk2BusyTime + finishingTime;

            disk2ResponseTotal = disk2ResponseTotal + (finishingTime - processingEvent.time);

            if(finishingTime - processingEvent.time > disk2ResponseMax){
                disk2ResponseMax = finishingTime - processingEvent.time;
            }
        }

        eqTotal = eqTotal + eventQueue->currentSize;
        cpuTotal = cpuTotal + cpuQueue->rear;
        disk1Total = disk1Total + disk1->rear;
        disk2Total = disk2Total + disk2->rear;

        if(eventQueue->currentSize > eqMax){
            eqMax = eventQueue->currentSize;
        }
        if(cpuQueue->rear > cpuMax){
            cpuMax = cpuQueue->rear;
        }
        if(disk1->rear > disk1Max){
            disk1Max = disk1->rear;
        }
        if(disk2->rear > disk2Max){
            disk2Max = disk2->rear;
        }
        numOfRuns++;
/*
        printEQ(eventQueue);
        printf("CPU Queue: ");
        printFIFO(cpuQueue);
        printf("\n");
        printf("Disk1 Queue: ");
        printFIFO(disk1);
        printf("\n");
        printf("Disk2 Queue: ");
        printFIFO(disk2);
        printf("\n");
        printf("runtime%d\n", runTime);*/
    }

    fclose(log);
    destroy(eventQueue);
    destroyFIFO(cpuQueue);
    destroyFIFO(disk1);
    destroyFIFO(disk2);

    printf("Simulation Ended\n");

    printf("\nAverage Queue Sizes\n");
    printf("Event Queue: %d\n", eqTotal/numOfRuns);
    printf("CPU Queue: %d\n", cpuTotal/numOfRuns);
    printf("Disk1 Queue: %d\n", disk1Total/numOfRuns);
    printf("Disk2 Queue: %d\n", disk2Total/numOfRuns);

    printf("\nMaximum Queue Sizes\n");
    printf("Event Queue: %d\n", eqMax);
    printf("CPU Queue: %d\n", cpuMax);
    printf("Disk1 Queue: %d\n", disk1Max);
    printf("Disk2 Queue: %d\n", disk2Max);

    printf("\nUtilization\n");
    printf("CPU: %d", cpuBusyTime/(FIN_TIME-INIT_TIME));
    printf("%%\n");
    printf("Disk1: %d", disk1BusyTime/(FIN_TIME-INIT_TIME));
    printf("%%\n");
    printf("Disk2: %d", disk2BusyTime/(FIN_TIME-INIT_TIME));
    printf("%%\n");

    printf("\nAverage Response Time\n");
    printf("CPU: %d\n", cpuResponseTotal/numOfRuns);
    printf("Disk1: %d\n", disk1ResponseTotal/numOfRuns);
    printf("Disk2: %d\n", disk2ResponseTotal/numOfRuns);

    printf("\nMaximum Response Time\n");
    printf("CPU: %d\n", cpuResponseMax);
    printf("Disk1: %d\n", disk1ResponseMax);
    printf("Disk2: %d\n", disk2ResponseMax);

    printf("\nThroughput\n");
    printf("CPU: %f", (float)cpuCompleted/(FIN_TIME-INIT_TIME));
    printf(" jobs per time unit\n");
    printf("Disk1: %f", (float)disk1Completed/(FIN_TIME-INIT_TIME));
    printf(" jobs per time unit\n");
    printf("Disk2: %f", (float)disk2Completed/(FIN_TIME-INIT_TIME));
    printf(" jobs per time unit\n");

    return 0;
}

int randGen(int min, int max){
    int num = (rand() % (max - min + 1)) + min;
    return num;
}
