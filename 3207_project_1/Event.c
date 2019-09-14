#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Event.h"

Event createEvent(int id, int type, int time){
    Event job = {id, type, time};
    return job;
}

void printEvent(Event job){
    if(job.type == 0){
        printf("SIM_START at %d", job.time);
            //event
    }
    else if(job.type == 1){
        printf("SIM_END at %d", job.time);
            //event
    }
    else{
        printf("At time %d ", job.time);
        printf("job%d ", job.id);
        if(job.type == 2){
            printf("arrives at CPU.");
        }
        else if(job.type == 3){
            printf("finishes at CPU.");
        }
        else if(job.type == 4){
            printf("arrives at disk1.");
        }
        else if(job.type == 5){
            printf("finishes at disk1.");
        }
        else if(job.type == 6){
            printf("arrives at disk2.");
        }
        else if(job.type == 7){
            printf("finishes at disk2.");
        }
        else if(job.type == 8){
            printf("exits.");
        }
    }
}
