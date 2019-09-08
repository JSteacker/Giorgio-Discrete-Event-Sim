#ifndef FIFOQUEUE_H_INCLUDED
#define FIFOQUEUE_H_INCLUDED
#include "Event.h"

typedef struct{
    int front;
    int rear;
    int capacity;
    Event *eventList;
} FIFOQueue;

FIFOQueue *initialize(int capacity);
void insertFIFO(FIFOQueue *fifo, Event event);
void removeFIFO(FIFOQueue *fifo);
void printFIFO(FIFOQueue *fifo);
void destroyFIFO(FIFOQueue *fifo);
int isFullFIFO(FIFOQueue *fifo);
int isEmptyFIFO(FIFOQueue *fifo);
#endif
