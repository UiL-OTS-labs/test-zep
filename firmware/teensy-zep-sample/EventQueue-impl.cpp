
#include "Events.h"
#include "CyclicQueue.h"
#include "EventQueue-impl.h"

template class CyclicQueue<std::shared_ptr<EventPtr>>;
//template class EventQueue;

//EventQueue gqueue(64);
