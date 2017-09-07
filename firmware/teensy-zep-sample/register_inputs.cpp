
#include "WProgram.h"
#include "register_inputs.h"
#include "Events.h"
#include "CyclicQueue.h"
#include "EventQueue-impl.h"
#include "Clock.h"

//typedef CyclicQueue<EventPtr> EventQueue;
extern EventQueue gqueue;

void change0()
{
    unsigned long us = gclock.time();
    const int pin = 0;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change1()
{
    unsigned long us = gclock.time();
    const int pin = 1;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change2()
{
    unsigned long us = gclock.time();
    const int pin = 2;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change3()
{
    unsigned long us = gclock.time();
    const int pin = 3;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change4()
{
    unsigned long us = gclock.time();
    const int pin = 4;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change5()
{
    unsigned long us = gclock.time();
    const int pin = 5;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change6()
{
    unsigned long us = gclock.time();
    const int pin = 6;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change7()
{
    unsigned long us = gclock.time();
    const int pin = 7;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change8()
{
    unsigned long us = gclock.time();
    const int pin = 8;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change9()
{
    unsigned long us = gclock.time();
    const int pin = 9;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change10()
{
    unsigned long us = gclock.time();
    const int pin = 10;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change11()
{
    unsigned long us = gclock.time();
    const int pin = 11;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change12()
{
    unsigned long us = gclock.time();
    const int pin = 12;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change13()
{
    unsigned long us = gclock.time();
    const int pin = 13;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change14()
{
    unsigned long us = gclock.time();
    const int pin = 14;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change15()
{
    unsigned long us = gclock.time();
    const int pin = 15;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change16()
{
    unsigned long us = gclock.time();
    const int pin = 16;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change17()
{
    unsigned long us = gclock.time();
    const int pin = 17;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change18()
{
    unsigned long us = gclock.time();
    const int pin = 18;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change19()
{
    unsigned long us = gclock.time();
    const int pin = 19;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change20()
{
    unsigned long us = gclock.time();
    const int pin = 20;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change21()
{
    unsigned long us = gclock.time();
    const int pin = 21;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change22()
{
    unsigned long us = gclock.time();
    const int pin = 22;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

void change23()
{
    unsigned long us = gclock.time();
    const int pin = 23;
    int level = digitalRead(pin);
    gqueue.enqueue(std::make_shared<TriggeredEvent>(us, pin, level));
}

int registerInputTrigger(uint8_t line)
{
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
    if (line < 24) {
        detachInterrupt(line);
    }
    else {
        err = 1;
    }
    return 0;
}

