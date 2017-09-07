
#ifndef EVENTS_H
#define EVENTS_H

#include <stdint.h>
#include <memory>

class Event {
    
    public:

        enum Type {
            TRIGGERED
        };

        Event(Type type, uint64_t time);
        virtual ~Event()
        {
        }
        
        Type        mtype;
        uint64_t    mtime;           // The Time of the event.
};

typedef std::shared_ptr<Event> EventPtr;

class TriggeredEvent : public Event {
    
    public:

        TriggeredEvent(uint64_t time, uint8_t pin, uint8_t llevel);
    
        uint8_t     mpin;            // The pin on which the event occurred.
        uint8_t     mlogic_level;    // The logic level after the event.
};

typedef std::shared_ptr<TriggeredEvent> TriggeredEventPtr;

#endif //define EVENTS_H
