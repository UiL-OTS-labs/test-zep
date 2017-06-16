
/*standard c headers*/
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/*Our header*/
#include "libteensy.h" 
/*Posix headers*/
#if defined(__unix__) || defined(__APPLE__)
#include <poll.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#elif defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#if defined(_WIN32)
typedef HANDLE TeensyDev;
typedef struct _COMMCONFIG  teensy_serial_settings;
#else
typedef int TeensyDev;
typedef struct termios teensy_serial_settings;
#endif 

typedef struct _TeensyClass {
    size_t instance_size;
    int  (*poll)    (TeensyDevice* self, int ms);
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

TeensyClass teensy_class;

void teensy_init(TeensyDevice* self);

int tpoll(TeensyDevice* self, int ms) {
    assert(self && self->class == &teensy_class);
    int ret;
    int poll_ms = ms;
    if (!teensy_is_open(self))
        return TEENSY_NOT_OPEN;

#if defined(_WIN32)
    int nhandles = 1;
    ret = WaitForMultipleObjects(nhandles, &self->device, FALSE, poll_ms);
    if (ret == WAIT_TIMEOUT)
        return TEENSY_TIMEOUT;
    else if (ret >= WAIT_OBJECT_0)
        return TEENSY_OK;
    else
        return TEENSY_GENERAL_ERROR;
#else

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
    return ret;
#endif
}

void tinit(TeensyDevice* self) {
    assert(self && self->class == &teensy_class);
#if defined(_WIN32)
    self->device = INVALID_HANDLE_VALUE;
#else
    self->device = -1;
#endif
}

int topen(TeensyDevice* self, const char* dev) {
    assert(self && self->class == &teensy_class);
    int ret;
    if (!self)
        return TEENSY_GENERAL_ERROR;
#if defined(_WIN32)
    // I just don't get why they don't use size_t to specify 
    // the size of a struct...
    DWORD commsz = (DWORD)sizeof(self->def_settings);
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

    ret = GetCommConfig(self->device, &self->def_settings, &commsz);
    if (ret == FALSE)
        return TEENSY_GENERAL_ERROR;

    self->raw_settings = self->def_settings;

    ret = SetCommConfig(self->device, &self->raw_settings, commsz);
    if (ret == FALSE) {
        fprintf(stderr, "Unable to set commsettings\n");
        return TEENSY_GENERAL_ERROR;
    }
    // TODO check whether the original settings work for teensy.
    
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
#if defined(_WIN32)
    CloseHandle(self->device);
    self->device = INVALID_HANDLE_VALUE;
#else
    int ret;
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
    DWORD retsize;
    if (ReadFile(self->device, buffer, size, &retsize, NULL) == FALSE){
        DWORD lerror = GetLastError();
        if (lerror == ERROR_MORE_DATA)
            return retsize;
        return -1;
    }
    ret = retsize;
    return ret;
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
    DWORD retsize;
    if (WriteFile(self->device, buffer, size, &retsize, NULL) == FALSE) {
        return -1;
    }
    ret = retsize;
    return ret;
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

int teensy_poll(TeensyDevice* self, int ms) {
    struct _Teensy* device =  self;
    assert(device->class == &teensy_class);
    const TeensyClass* cls = device->class;

    return cls->poll(self, ms);
}

void teensy_init(TeensyDevice* self) {
    assert(self->class == &teensy_class);
    const TeensyClass* cls = self->class;
    cls->init(self);
}

int teensy_is_open(TeensyDevice* self) {
    assert(self && self->class == &teensy_class);
    return self->class->is_open(self);
}

int teensy_open(TeensyDevice* self, const char* dev) {
    assert(self && self->class == &teensy_class);
    return self->class->open(self, dev);
}
void teensy_close(TeensyDevice* self) {
    assert(self && self->class == &teensy_class);
    self->class->close(self);
}

void teensy_destroy(TeensyDevice* self) {
    assert(self && self->class == &teensy_class);
    self->class->destroy(self);
}

int teensy_read(TeensyDevice* self, char* buffer, size_t size) {
    assert(self && self->class == &teensy_class);
    return self->class->read(self, buffer, size);
}

int teensy_write(TeensyDevice* self, const char* buffer, size_t size) {
    assert(self && self->class == &teensy_class);
    return self->class->write(self, buffer, size);
}
