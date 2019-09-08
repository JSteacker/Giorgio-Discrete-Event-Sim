#include <stdio.h>
#include <stdlib.h>

#include "PriorityQueue.h"
#include "FIFOQueue.h"
#include "Event.h"


int INIT_TIME = 0;
int FIN_TIME = 10;
int EQ_CAPACITY = 10;
int CPU_CAPACITY = 10;
int DISK_CAPACITY = 10;

/*
    Main loop of the simulator. Runs from INIT_TIME to FIN_TIME
*/
int main(){
    int runTime = INIT_TIME;

    PriorityQueue *eventQueue = initalizeEQ(EQ_CAPACITY);
    FIFOQueue *cpu = initialize(CPU_CAPACITY);
    FIFOQueue *disk1 = initialize(DISK_CAPACITY);
    FIFOQueue *disk2 = initialize(DISK_CAPACITY);



    while(runTime < FIN_TIME){
        printf("Time = %d", runTime);
        printf("\n");
        runTime++;
    }

    eventQInsert(eventQueue, createEvent(0,0,0));
    Event job2 = {2, 2, 10};
    Event job3 = {3, 1, 30};
    Event job4 = {4, 2, 20};
    Event job5 = {5, 2, 12};
    Event job6 = {6, 2, 5};
    Event job7 = {7, 2, 11};
    Event job8 = {8, 2, 8};
    printEQ(eventQueue);
    printf("\n");
    eventQInsert(eventQueue, job2);
    printEQ(eventQueue);
    printf("\n");
    eventQInsert(eventQueue, job3);
    printEQ(eventQueue);
    printf("\n");
    eventQInsert(eventQueue, job4);
    printEQ(eventQueue);
    printf("\n");
    eventQInsert(eventQueue, job5);
    printEQ(eventQueue);
    printf("\n");
    eventQInsert(eventQueue, job6);
    printEQ(eventQueue);
    printf("\n");
    eventQInsert(eventQueue, job7);
    printEQ(eventQueue);
    printf("\n");

    popMin(eventQueue);
    printEQ(eventQueue);
    printf("\n");

    eventQInsert(eventQueue, job8);
    printEQ(eventQueue);
    printf("\n");

    insertFIFO(cpu, popMin(eventQueue));
    insertFIFO(cpu, popMin(eventQueue));
    removeFIFO(cpu);
    printEQ(eventQueue);
    printf("\n");
    printFIFO(cpu);
    printf("\n");

    destroy(eventQueue);
    destroyFIFO(cpu);
    destroyFIFO(disk1);
    destroyFIFO(disk2);
    return 0;
}

