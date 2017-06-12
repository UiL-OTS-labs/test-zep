
/*standard c headers*/
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libteensy.h" 
/*Posix headers*/
#include <poll.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#if defined(_WIN32)
typedef HANDLE TeensyDev;
typedef struct _COMMCONFIG  teensy_serial_settings;
#else
typedef int TeensyDev;
typedef struct termios teensy_serial_settings;
#endif 

typedef struct _TeensyClass {
    size_t instance_size;
    int  (*poll)    (TeensyDevice* self);
    int  (*open)    (TeensyDevice* self, const char* device);
    int  (*is_open) (TeensyDevice* self);
    void (*init)    (TeensyDevice* self);
    void (*close)   (TeensyDevice* self);
    void (*destroy) (TeensyDevice* self);
    int  (*read)    (TeensyDevice* self, char* buffer, size_t size);
    int  (*write)   (TeensyDevice* self, const char* buffer, size_t size);
} TeensyClass;

struct _Teensy {
    const TeensyClass*      class;
    TeensyDev               device;
    teensy_serial_settings  def_settings;
    teensy_serial_settings  raw_settings;
};

void teensy_init();

int tpoll(TeensyDevice* self) {
    int ret;
    int poll_ms = 1000;
#if defined(_WIN32)

#else
    assert(self);
    if (!teensy_is_open(self)) 
        return TEENSY_NOT_OPEN;
    struct pollfd p;
    p.fd = self->device;
    p.events = POLLIN;
    ret = poll(&p, 1, poll_ms);
    if (ret > 0)
        ret = TEENSY_OK;
    else if (ret == 0)
        ret = TEENSY_TIMEOUT;
    else
        ret = TEENSY_GENERAL_ERROR;
#endif
    return ret; 
}

void tinit(TeensyDevice* self) {
    assert(self);
#if defined(_WIN32)
    self->device = INVALID_HANDLE_VALUE;
#else
    self->device = -1;
#endif
}

int topen(TeensyDevice* self, const char* dev) {
    assert(self);
    int ret;
    if (!self)
        return TEENSY_GENERAL_ERROR;
#if defined(_WIN32)
    self->device = CreateFile(
            dev,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL
            );

    if (self->device == INVALID_HANDLE_VALUE)
        return TEENSY_NOT_OPEN;
#else
    assert(self);
    self->device = open(dev, O_RDWR | O_TRUNC | O_NOCTTY | O_NONBLOCK);
    if (self->device < 0) {
        return TEENSY_NOT_OPEN;
    }

    ret = tcgetattr(self->device, &self->def_settings);
    if (ret) {
        fprintf(stderr, "Unable to get terminal settings.\n");
        return TEENSY_GENERAL_ERROR;
    }

    cfmakeraw(&self->raw_settings);

    ret = tcsetattr(self->device, TCSANOW, &self->raw_settings);
    if (ret) {
        fprintf(stderr, "Unable to apply raw terminal settings.\n");
        return TEENSY_GENERAL_ERROR;
    }
    
#endif
    return TEENSY_OK;
}

int tisopen(TeensyDevice* self) {
    int ret;
#if defined(_WIN32)
    ret = self->device != INVALID_HANDLE_VALUE;
#else
    ret = self->device >= 0;
#endif
    return ret;
}

void tclose(TeensyDevice* self) {
    int ret;
#if defined(_WIN32)
    CloseHandle(self->device);
    self->device = INVALID_HANDLE_VALUE;
#else
    ret = tcsetattr(self->device, TCSAFLUSH, &self->def_settings);
    if (ret)
        fprintf(stderr, "Unable to restore default settings.\n");

    close(self->device);
    self->device = -1;
#endif
}

void tdestroy(TeensyDevice* self) {
    if(teensy_is_open(self))
        teensy_close(self);
    free(self);
}

int tread(TeensyDevice* self, char* buffer, size_t size)
{
    int ret;
    if (!teensy_is_open(self) )
        return TEENSY_NOT_OPEN;

#if defined(_WIN32)
#else
    ret = read(self->device, buffer, size);
    if (ret == -1)
        return  TEENSY_INTERRUPTED;
    if (ret < -1)
        return TEENSY_GENERAL_ERROR;
    return ret;
#endif
}

int twrite(TeensyDevice* self, const char* buffer, size_t size)
{
    int ret;
    if (!teensy_is_open(self) )
        return TEENSY_NOT_OPEN;

#if defined(_WIN32)
#else
    ret = write(self->device, buffer, size);
    if (ret == -1)
        return  TEENSY_INTERRUPTED;
    if (ret < -1)
        return TEENSY_GENERAL_ERROR;
    return ret;
#endif
}

struct _TeensyClass teensy_class = { 
    sizeof(struct _Teensy),
    tpoll,
    topen,
    tisopen,
    tinit,
    tclose,
    tdestroy,
    tread,
    twrite
};

TeensyDevice* teensy_new()
{
    struct _Teensy* teensy = malloc(teensy_class.instance_size);
    if (!teensy)
        return NULL;

    teensy->class = &teensy_class;
    teensy_init(teensy);

    return teensy;
}

int teensy_poll(TeensyDevice* self) {
    struct _Teensy* device =  self;
    assert(device->class == &teensy_class);
    const TeensyClass* cls = device->class;

    return cls->poll(self);
}

void teensy_init(TeensyDevice* self) {
    assert(self->class == &teensy_class);
    const TeensyClass* cls = self->class;
    cls->init(self);
}

