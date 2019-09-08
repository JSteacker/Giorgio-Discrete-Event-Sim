/* In general it's good to include also the header of the current .c,
   to avoid repeating the prototypes */
#include <stdio.h>
#include <stdlib.h>
#include "PriorityQueue.h"

//Initialize the Event Queue
PriorityQueue *initalizeEQ(int capacity){
    PriorityQueue *eq = (PriorityQueue * ) malloc(sizeof(PriorityQueue));
    if(eq == NULL){
        printf("Error!");
        return;
    }
    eq->capacity = capacity;
    eq->currentSize = 0;
    eq->eventList = (Event *) malloc(capacity*sizeof(Event)); //size in bytes

    //check if allocation succeed
    if (eq->eventList == NULL){
        printf("Memory Error!");
        return;
    }
    printf("Initializing event queue successful!\n");
    return eq;
}

void eventQInsert(PriorityQueue *eq, Event event){
    if(!isFull(eq)){
        eq->eventList[eq->currentSize] = event;
        heapBotTop(eq, eq->currentSize);
        eq->currentSize++;
    }
    else{
        printf("Priority Queue full, insert failed!");
    }
}

/*
    Heapify's from the bottom to the top
*/
void heapBotTop(PriorityQueue *eq, int index){
    Event temp;
    int parent_event = (index-1)/2;

    //If parent is greater than new entry
    if(eq->eventList[parent_event].time > eq->eventList[index].time){
        //swap and recursive call
        temp = eq->eventList[parent_event];
        eq->eventList[parent_event] = eq->eventList[index];
        eq->eventList[index] = temp;
        //continue up tree from the smallest
        heapBotTop(eq, parent_event);
    }
    //If new entry is greater than previous
    if(eq->eventList[index].time < eq->eventList[index-1].time && index != 0){
        temp = eq->eventList[index];
        eq->eventList[index] = eq->eventList[index-1];
        eq->eventList[index-1] = temp;
        index--;
        heapBotTop(eq, index);
    }
}

/*
    Pops the first event of the event queue
*/
Event popMin(PriorityQueue *eq){
    Event pop;

    if(isEmpty(eq)){
        printf("\nEvent Queue is empty!\n");
        return;
    }

    pop = eq->eventList[0];
    int j;
    for(int i = 0; i<eq->currentSize-1; i++){
        j = i+1;
        eq->eventList[i] = eq->eventList[j];
    }
    eq->currentSize--;
    return pop;
}

void printEQ(PriorityQueue *eq){
    int i;
    for(i=0;i< eq->currentSize;i++){
        if(eq->eventList[i].id != 0 && eq->eventList[i].id != 1000000){
            printf("job%d", eq->eventList[i].id);
        }
        if(eq->eventList[i].type == 0){
            printf(",SIM_START,");
            //event
        }
        else if(eq->eventList[i].type == 1){
            printf(",SIM_END,");
            //event
        }
        else if(eq->eventList[i].type == 2){
            printf(",Arrival,");
        }
        printf("%d", eq->eventList[i].time);
        printf("\n");
    }
}

void destroy(PriorityQueue *eq){
    free(eq->eventList);
}

int isFull(PriorityQueue *eq){
    if(eq->capacity == eq->currentSize){
        return 1;
    }
    else{
        return 0;
    }
}

int isEmpty(PriorityQueue *eq){
    if(eq->currentSize == 0){
        return 1;
    }
    else{
        return 0;
    }
}
