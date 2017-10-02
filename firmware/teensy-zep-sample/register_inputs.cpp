
#include "WProgram.h"
#include "register_inputs.h"
#include "InterruptLock.h"
#include "Events.h"
#include "CyclicQueue.h"
#include "EventQueue-impl.h"
#include "Clock.h"
#include <vector>

/* ************* declarations *********** */

extern EventQueue gqueue;
static void queuePinEvent(const int pin);

#define MAX_PINS 24


/* ************* pin states ************ */

PinState g_pinstates[MAX_PINS];

/* ************* implementation of Pinstate *************/

PinState::PinState()
    :
        m_state(0)
{
}

PinState::PinState(const PinState& other)
{
    *this = other;
}

PinState::PinState(uint8_t state)
    :
        m_state(state)
{
}

PinState& PinState::operator=(const PinState& rhs)
{
    m_state = rhs.m_state;
    return *this;
}

uint8_t PinState::state() const
{
    return m_state;
}

void PinState::setLogicLevel(int level)
{
    if (level)
        m_state |= LOGIC_HIGH;
    else
        m_state &= ~LOGIC_HIGH;
}

bool PinState::logicLevel() const
{
    return (m_state & LOGIC_HIGH) != 0;
}

void PinState::flipLogicLevel()
{
    m_state ^= LOGIC_HIGH;
}

/* ******** Interrupt Service Routines *********** */

static void change0()
{
    queuePinEvent(0);
}

static void change1()
{
    queuePinEvent(1);
}

static void change2()
{
    queuePinEvent(2);
}

static void change3()
{
    queuePinEvent(3);
}

static void change4()
{
    queuePinEvent(4);
}

static void change5()
{
    queuePinEvent(5);
}

static void change6()
{
    queuePinEvent(6);
}

static void change7()
{
    queuePinEvent(7);
}

static void change8()
{
    queuePinEvent(8);
}

static void change9()
{
    queuePinEvent(9);
}

static void change10()
{
    queuePinEvent(10);
}

static void change11()
{
    queuePinEvent(11);
}

static void change12()
{
    queuePinEvent(12);
}

static void change13()
{
    queuePinEvent(13);
}

static void change14()
{
    queuePinEvent(14);
}

static void change15()
{
    queuePinEvent(15);
}

static void change16()
{
    queuePinEvent(16);
}

static void change17()
{
    queuePinEvent(17);
}

static void change18()
{
    queuePinEvent(18);
}

static void change19()
{
    queuePinEvent(19);
}

static void change20()
{
    queuePinEvent(20);
}

static void change21()
{
    queuePinEvent(21);
}

static void change22()
{
    queuePinEvent(22);
}

static void change23()
{
    queuePinEvent(23);
}

/* ******** functions *********** */

static void queuePinEvent(const int pin)
{
    uint64_t us = gclock.time();
    if (pin < 0 || pin >= MAX_PINS)
        return; // oops...

    int logic_level;  
    {
        InterruptLock lock;
        logic_level = digitalRead(pin);
    }

    g_pinstates[pin].setLogicLevel(logic_level);
    uint8_t  level = g_pinstates[pin].state() & PinState::LOGIC_HIGH ? 1 : 0;

    if (g_pinstates[pin].state() & PinState::SINGLE_SHOT) {
        deregisterInputTrigger(pin);
        g_pinstates[pin] = PinState();
    }

    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

int registerInputTrigger(uint8_t line, bool single_shot)
{
    uint8_t state = PinState::REGISTERED;
    state |= digitalRead(line) == HIGH ? PinState::LOGIC_HIGH : 0;
    state |= single_shot ? PinState::SINGLE_SHOT : 0;
    
    if (line < MAX_PINS) // perhaps a bit pedantic...
        g_pinstates[line] = PinState(state);
    else
        return -1;

    switch(line) {
        case 0:
            attachInterrupt(line, change0, CHANGE);
            break;
        case 1:
            attachInterrupt(line, change1, CHANGE);
            break;
        case 2:
            attachInterrupt(line, change2, CHANGE);
            break;
        case 3:
            attachInterrupt(line, change3, CHANGE);
            break;
        case 4:
            attachInterrupt(line, change4, CHANGE);
            break;
        case 5:
            attachInterrupt(line, change5, CHANGE);
            break;
        case 6:
            attachInterrupt(line, change6, CHANGE);
            break;
        case 7:
            attachInterrupt(line, change7, CHANGE);
            break;
        case 8:
            attachInterrupt(line, change8, CHANGE);
            break;
        case 9:
            attachInterrupt(line, change9, CHANGE);
            break;
        case 10:
            attachInterrupt(line, change10, CHANGE);
            break;
        case 11:
            attachInterrupt(line, change11, CHANGE);
            break;
        case 12:
            attachInterrupt(line, change12, CHANGE);
            break;
        case 13:
            attachInterrupt(line, change13, CHANGE);
            break;
        case 14:
            attachInterrupt(line, change14, CHANGE);
            break;
        case 15:
            attachInterrupt(line, change15, CHANGE);
            break;
        case 16:
            attachInterrupt(line, change16, CHANGE);
            break;
        case 17:
            attachInterrupt(line, change17, CHANGE);
            break;
        case 18:
            attachInterrupt(line, change18, CHANGE);
            break;
        case 19:
            attachInterrupt(line, change19, CHANGE);
            break;
        case 20:
            attachInterrupt(line, change20, CHANGE);
            break;
        case 21:
            attachInterrupt(line, change21, CHANGE);
            break;
        case 22:
            attachInterrupt(line, change22, CHANGE);
            break;
        case 23:
            attachInterrupt(line, change23, CHANGE);
            break;
        default:
            return -1;
    }
    return 0;
}

int deregisterInputTrigger(uint8_t line)
{
    int err = 0;
    if (line < MAX_PINS) {
        detachInterrupt(line);
        g_pinstates[line] = PinState();
    }
    else {
        err = 1;
    }
    return err;
}

void clearPinStates()
{
    for (unsigned i = 0; i < MAX_PINS; ++i)
        g_pinstates[i] = PinState();
}
