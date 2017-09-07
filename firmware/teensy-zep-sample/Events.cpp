
#include "Events.h"

Event::Event(Type type, uint64_t time)
    : 
        mtype(type),
        mtime(time)
{
}

TriggeredEvent::TriggeredEvent( uint64_t time, uint8_t pin, uint8_t llevel)
    :
        Event(Event::TRIGGERED, time),
        mpin(pin),
        mlogic_level(llevel)
    
{
}


