#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED
#include "Event.h"
/* ^^ these are the include guards */

//THIS IS THE PRIORITY QUEUE
typedef struct{
    int capacity;
    int currentSize;
    Event *eventList;
} PriorityQueue;

/* Prototypes for the functions */
PriorityQueue *initalizeEQ(int capacity);
void eventQInsert(PriorityQueue *eq, Event event);
void heapBotTop(PriorityQueue *eq, int index);
Event popMin(PriorityQueue *eq);
void printEQ(PriorityQueue *eq);
void destroy(PriorityQueue *eq);
int isFull(PriorityQueue *eq);
int isEmpty(PriorityQueue *eq);
#endif
