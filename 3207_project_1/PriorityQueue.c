#include <stdio.h>
#include <stdlib.h>
#include "PriorityQueue.h"

//Initialize the Event Queue
PriorityQueue *initalizePQ(int capacity){
    PriorityQueue *pq = (PriorityQueue * ) malloc(sizeof(PriorityQueue));
    if(pq == NULL){
        printf("Error!");
        return;
    }
    pq->capacity = capacity;
    pq->currentSize = 0;
    pq->eventList = (Event *) malloc(capacity*sizeof(Event)); //size in bytes

    //check if allocation succeed
    if (pq->eventList == NULL){
        printf("Memory Error!");
        return;
    }
    return pq;
}

void priorityQInsert(PriorityQueue *pq, Event event){
    if(!isFull(pq)){
        pq->eventList[pq->currentSize] = event;
        heapBotTop(pq, pq->currentSize);
        pq->currentSize++;
    }
    else{
        printf("Priority Queue full, insert failed!");
    }
}

/*
    Heapify's from the bottom to the top
*/
void heapBotTop(PriorityQueue *pq, int index){
    Event temp;
    int parent_event = (index-1)/2;

    //If parent is greater than new entry
    if(pq->eventList[parent_event].time > pq->eventList[index].time){
        //swap and recursive call
        temp = pq->eventList[parent_event];
        pq->eventList[parent_event] = pq->eventList[index];
        pq->eventList[index] = temp;
        //continue up tree from the smallest
        heapBotTop(pq, parent_event);
    }
    //If new entry is greater than previous
    if(pq->eventList[index].time < pq->eventList[index-1].time && index != 0){
        temp = pq->eventList[index];
        pq->eventList[index] = pq->eventList[index-1];
        pq->eventList[index-1] = temp;
        index--;
        heapBotTop(pq, index);
    }
}

/*
    Pops the first event of the event queue
*/
Event popMin(PriorityQueue *pq){
    Event pop;

    if(isEmpty(pq)){
        printf("\nEvent Queue is empty!\n");
        return;
    }

    pop = pq->eventList[0];
    int j;
    for(int i = 0; i<pq->currentSize-1; i++){
        j = i+1;
        pq->eventList[i] = pq->eventList[j];
    }
    pq->currentSize--;
    return pop;
}

void printPQ(PriorityQueue *pq){
    int i;
    for(i=0;i< pq->currentSize;i++){
        printEvent(pq->eventList[i]);
        printf("\n");
    }
}

void destroy(PriorityQueue *pq){
    free(pq->eventList);
}

int isFull(PriorityQueue *pq){
    if(pq->capacity == pq->currentSize){
        return 1;
    }
    else{
        return 0;
    }
}

int isEmpty(PriorityQueue *pq){
    if(pq->currentSize == 0){
        return 1;
    }
    else{
        return 0;
    }
}
