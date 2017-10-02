
#ifndef CLOCK_H
#define CLOCK_H 

#include "Arduino.h"
#include <stdint.h>

/**
 * Clocks every 10 us.
 *
 * Clock is expected to be working longer than the lifetime of the Teensy.
 */
class Clock {

    public:

        Clock();

        void reset();
        uint64_t time() const;
        void setTime(uint64_t t);

        void start();
        void stop();

    private:
        
        static void _clock_inc_time();

        IntervalTimer       mtimer;
        volatile uint64_t   mtime;
        static const int    TICK = 10; //update clock every 10 us.
};

extern Clock gclock;

#endif // define CLOCK_H
