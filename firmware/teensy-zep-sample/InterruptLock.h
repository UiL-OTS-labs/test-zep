
#ifndef INTERRUPT_LOCK_H
#define INTERRUPT_LOCK_H

#include "WProgram.h"

/**
 * A class that disables interrupts when instantiated and enables them
 * once more via the destructor.
 */

class InterruptLock {

    public:

        InterruptLock()
        {
            noInterrupts();
        }

        ~InterruptLock()
        {
            interrupts();
        }
};

#endif
