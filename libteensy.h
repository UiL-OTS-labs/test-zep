
#ifndef LIBTEENSY_H
#define LIBTEENSY_H

#ifdef __cplusplus
extern "C" {
#endif

struct _Teensy;
typedef struct _Teensy TeensyDevice;

enum TeensyError {
    TEENSY_GENERAL_ERROR = -10000,
    TEENSY_NOT_OPEN,
    TEENSY_INTERRUPTED,
    TEENSY_OK = 0,
    TEENSY_TIMEOUT,
    TEENSY_NO_DATA
};

TeensyDevice* teensy_new();
int     teensy_poll(TeensyDevice* self);
int     teensy_open(TeensyDevice*self, const char* device);
int     teensy_is_open(TeensyDevice* self);
void    teensy_close(TeensyDevice* self);
void    teensy_destroy(TeensyDevice* self);
int     teensy_read(TeensyDevice* self, char** buffer);
int     teensy_write(TeensyDevice* self, const char* buffer, size_t size);

const char* teensy_error();

#ifdef __cplusplus
}
#endif

// #define LIBTEENSY_H
#endif
