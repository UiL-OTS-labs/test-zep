

#include "WProgram.h"
#include "Clock.h"
#include "InterruptLock.h"

// Global clock for entire teensy.
Clock gclock;

Clock::Clock()
{
    reset();
}

void Clock::reset()
{
    InterruptLock lock;
    mtime = 0;
}

uint64_t Clock::time() const
{
    uint64_t t;
    {
        InterruptLock lock;
        t = mtime;
    }

    t *= TICK;
    return t;
}

void Clock::setTime(uint64_t t)
{
    uint64_t new_ticks = t / TICK;
    InterruptLock lock;
    mtime = new_ticks;
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
    InterruptLock lock;
    gclock.mtime++;
}


