#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

// ID: "job1, job2, etc.", EVENT TYPE: "arrives, finishes at CPU, arrives at disk, finishes IO at disk, exits", TIME: num generator
typedef struct{
    int id;
    int type;
    int time;
} Event;

Event createEvent(int id, int type, int time);
void printEvent(Event job);
#endif
