
#include "TeensyPackage.h"
#include "teensy_constants.h"
#include "register_inputs.h"
#include "Events.h"
#include "CyclicQueue.h"
#include "Clock.h"
#include "EventQueue-impl.cpp"

using namespace ZEPTEENSY;

#define MAX_PINS 24

/**
 * Global variables
 */
TeensyPackage   gpackage;
CyclicQueue<std::shared_ptr<Event>> gqueue(64);

// True once the client has successfully performed a handshake.
bool            gidentified = false;


/**
 * utility function to check whether the line is describes a pin/line
 * that can be used as GPIO with a line CHANGE interrupt capability .
 */
bool isAcceptableInput(uint8_t line) {
    // Modify for Arduinos
    // Uno types for example only support pin 2 & 3 as valid input trigger.
    return line < MAX_PINS;
}

/**
 * Handles and identify message, both teensy and zep exchange their uuid's
 */
int handleIndentify()
{
    const String expected(ZEP_ZEP_TO_TEENSY_UUID);
    const String reply(ZEP_TEENSY_TO_ZEP_UUID);
    const size_t bufsz = expected.length();
    char buf[bufsz] = {0};
    const uint8_t* payload = gpackage.payload();

    if (gpackage.payloadSize() != expected.length()) {
        gpackage.prepareAcknowledgeFailure();
        gpackage.write();
        return -1;
    }

    memcpy(buf, payload, gpackage.payloadSize());
    buf[gpackage.payloadSize()] = '\0';

    if (expected != buf) {
        gpackage.prepareAcknowledgeFailure();
        gpackage.write();
        return -1;
    }

    gpackage.prepareIdentify(reply.c_str(), reply.length());
    if (gpackage.write() != 0) {
        return -1;
    }

    return 0;
}

/**
 * Handles the registration of an input trigger.
 *
 * Specifying and invalid line is an error.
 */
int handleRegisterInput(bool singleshot=false)
{
    uint8_t line;
    memcpy(&line, gpackage.payload(), sizeof(line));
    if (isAcceptableInput(line)) {
        pinMode(line, INPUT_PULLUP);
        registerInputTrigger(line, singleshot);
        gpackage.prepareAcknowledgeSuccess();
        gpackage.write();
    }
    else {
        gpackage.prepareInvalidLine();
        gpackage.write();
        return -1;
    }

    return 0;
}

/**
 * Handles the deregistration of an input trigger.
 *
 * Specifying and invalid line is an error, but deregistering
 * a line that wasn't specified doesn't hurt, thus does not result in an
 * error.
 */
int handleDeregisterInput()
{
    uint8_t line;
    memcpy(&line, gpackage.payload(), sizeof(line));
    if (isAcceptableInput(line)) {
        pinMode(line, INPUT_PULLUP);
        deregisterInputTrigger(line);
        gpackage.prepareAcknowledgeSuccess();
        gpackage.write();
    }
    else {
        gpackage.prepareInvalidLine();
        gpackage.write();
        return -1;
    }

    return 0;
}

/**
 * Handles a request to get the current time from the teensy device.
 */
int handleTime()
{
    uint64_t time = gclock.time();
    gpackage.prepareAcknowledgeTime(time);
    gpackage.write();
    return 0;
}

/**
 * Set the time sent to ourselves.
 */
int handleTimeSet()
{
    uint64_t time;
    gpackage.readInt64(gpackage.payload(), static_cast<void*>(&time));
    gclock.setTime(time);
    gpackage.prepareAcknowledgeSuccess();
    gpackage.write();
    return 0;
}

/**
 * Reads precisely one packet from the serial device (if the packet is valid).
 * It handles the packet and sends a reply whether the packet was successfully
 * handled or an error when
 */
int readPackage()
{
    int result = gpackage.read();

    if (result)
        return result;

    switch (gpackage.type()) {
        case TeensyPackage::IDENTIFY:
            result = handleIndentify();
            if (!result)
                gidentified = true;
            break;
        case TeensyPackage::REGISTER_INPUT:
            if (gidentified) {
                result = handleRegisterInput();
                break;
            }
        case TeensyPackage::REGISTER_SINGLE_SHOT:
            if (gidentified) {
                result = handleRegisterInput(true);
                break;
            }
        case TeensyPackage::DEREGISTER_INPUT:
            if (gidentified) {
                result = handleDeregisterInput();
                break;
            }
        case TeensyPackage::TIME:
            if (gidentified) {
                result = handleTime();
                break;
            }
        case TeensyPackage::TIME_SET:
            if (gidentified) {
                result = handleTimeSet();
                break;
            }
        default:
            gpackage.prepareAcknowledgeFailure();
            gpackage.write();
            result = 1;
    }
    return result;
}

/*
 * Sends one event back to the client.
 */
int sendEvent(const EventPtr e)
{
    using std::static_pointer_cast;

    int err = 0;

    switch (e->mtype) {
    case Event::TRIGGERED:
        {
            const TriggeredEventPtr t =
                    static_pointer_cast<TriggeredEvent>(e);
            gpackage.prepareEventTrigger(t->mpin,
                                         t->mtime,
                                         t->mlogic_level
                                         );
            break;
        }
    default:
        return 1;
    };

    err = gpackage.write();
    Serial.flush();

    return err;
}

/*
 * This function handles the connection with the client. So it should have
 * and active connection before it enters and will keep running until
 * the serial connection with the client is terminated.
 */
void handleClient()
{
    while (Serial) {
        if(Serial.available()) {
            readPackage();
        }
        while (!gqueue.empty()) {
            EventPtr e;
            int err = gqueue.dequeue(e);
            if (err)
                continue;
            err = sendEvent(e);
        }
    }
}

// The setup function is run before the program starts and after each 
// connection to the device is terminated in order to reset the status
// for a new device.
void setup()
{
    Serial.begin(115200);// for a Teensy it is always 12Mbit.

    // Make sure no events are still in the queue, once something connects
    gqueue.clear();
    
    for(int i = 0; i < MAX_PINS; i++) {
        pinMode(i, INPUT);
        deregisterInputTrigger(i);
    }

    clearPinStates();

    pinMode(13, OUTPUT);

    // Cancel all running timers.
    gclock.stop();

    // require a new handshake.
    gidentified = false;
}


void loop()
{
    if (Serial) {
        gclock.reset();
        gclock.start();
        digitalWrite(13, HIGH);

        handleClient();
    }
    
    // Connection lost reinitialize default state.
    digitalWrite(13, LOW);
    setup();
}


