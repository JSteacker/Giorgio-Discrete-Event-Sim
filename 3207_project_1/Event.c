#include <stdio.h>
#include <stdlib.h>
#include "Event.h"

Event createEvent(int id, int type, int time){
    Event job = {id, type, time};
    return job;
}

Event changeEventType(Event event, int type){
    event.type = type;
    return event;
}

Event changeEventTime(Event event, int time){
    event.time = time;
    return event;
}
