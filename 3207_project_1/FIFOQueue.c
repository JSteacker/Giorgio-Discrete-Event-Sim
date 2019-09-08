#include <stdio.h>
#include <stdlib.h>
#include "FIFOQueue.h"

FIFOQueue *initialize(int capacity){
    FIFOQueue *fifo = (FIFOQueue * ) malloc(sizeof(FIFOQueue));
    if(fifo == NULL){
        printf("Error!");
        return;
    }
    fifo->capacity = capacity;
    fifo->front = 0;
    fifo->rear = 0;
    fifo->eventList = (Event *) malloc(capacity*sizeof(Event)); //size in bytes

    //check if allocation succeed
    if (fifo->eventList == NULL){
        printf("Memory Error!");
        return;
    }
    printf("Initializing fifo queue successful!\n");
    return fifo;
}

void insertFIFO(FIFOQueue *fifo, Event event){
    if(isFullFIFO(fifo)){
        return;
    }
    else{
        fifo->eventList[fifo->rear] = event;
        fifo->rear++;
    }
}

void removeFIFO(FIFOQueue *fifo){
    if(isEmptyFIFO(fifo)){
        return;
    }
    else{
        //shifts all events in queue
        for(int i = 0; i < fifo->rear-1; i++){
            fifo->eventList[i] = fifo->eventList[i+1];
        }
        fifo->rear--;
    }
}

void printFIFO(FIFOQueue *fifo){
        if (isEmptyFIFO(fifo)){
            printf("\nQueue is Empty\n");
            return;
        }

        // traverse front to rear and print elements
        for (int i = fifo->front; i < fifo->rear; i++) {
            printf("job%d,", fifo->eventList[i].id);
        }
}

void destroyFIFO(FIFOQueue *fifo){
    free(fifo->eventList);
}

int isFullFIFO(FIFOQueue *fifo){
    if(fifo->capacity == fifo->rear){
        return 1;
    }
    else{
        return 0;
    }
}

int isEmptyFIFO(FIFOQueue *fifo){
    if(fifo->front == fifo->rear){
        return 1;
    }
    else{
        return 0;
    }
}
