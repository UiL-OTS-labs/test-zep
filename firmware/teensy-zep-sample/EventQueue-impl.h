
#ifndef EVENQUEUE_IMPL_H
#define EVENQUEUE_IMPL_H


#include "Events.h"
#include "CyclicQueue.h"

typedef CyclicQueue<EventPtr> EventQueue;

extern EventQueue gqueue;

#endif //define EVENQUEUE_IMPL_H
