#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED
#include "Event.h"

//THIS IS THE PRIORITY QUEUE
typedef struct{
    int capacity;
    int currentSize;
    Event *eventList;
} PriorityQueue;

/* Prototypes for the functions */
PriorityQueue *initalizePQ(int capacity);
void priorityQInsert(PriorityQueue *pq, Event event);
void heapBotTop(PriorityQueue *pq, int index);
Event popMin(PriorityQueue *pq);
void printEQ(PriorityQueue *pq);
void destroy(PriorityQueue *pq);
int isFull(PriorityQueue *pq);
int isEmpty(PriorityQueue *pq);
#endif
