

#include "WProgram.h"
#include "Clock.h"

// Global clock for entire teensy.
Clock gclock;

Clock::Clock()
{
    reset();
}

void Clock::reset()
{
    mtime = 0;
}

uint64_t Clock::time() const
{
    // Make sure that an interrupt doesn't screw up the time.
    volatile uint64_t t = mtime;
    while (t != mtime)
        t = mtime;

    t *= TICK;
    return t;
}

void Clock::start()
{
    mtimer.priority(64);
    mtimer.begin(Clock::_clock_inc_time, TICK);
}

void Clock::stop()
{
    mtimer.end();
}

void Clock::_clock_inc_time()
{
    gclock.mtime++;
}


