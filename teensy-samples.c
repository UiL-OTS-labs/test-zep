
#ifdef _WIN32
// Hopefully this stops VisualStudio from nagging about functions
// not deprecated in C standards.
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdint.h>
#include <assert.h>

#include "parse-cmd.h"
#include "libteensy.h"

/*On windows eeg "COM1"*/
char device[1024]       = "/dev/ttyACM0";
char output_fn[1024]    = "./screen-output.txt";

//const char* optstr = "d:o:";
cmd_option arguments[] = {
    {'d', "device",             OPT_STR,    {0}},
    {'o', "output-filename",    OPT_STR,    {0}},
    {'v', "verbose",            OPT_FLAG,   {0}},
    {'h', "help",               OPT_FLAG,   {0}}              
};

volatile int interrupted = 0;
int stop = 0;

int verbose = 0;

void signal_handler(int signal) {
    (void)signal;
    interrupted = 1;
}

enum PackageType {
    START,
    STOP,
    HEADER,
    SAMPLE,
    SCREEN_INTERRUPT,
    SOUND_SAMPLE
};

struct Package {
    // Accommodate space for terminating null byte.
    uint8_t     buffer[256+1];
    uint8_t     size;
    uint8_t     type;

    uint32_t    time; // check whether uint32_t is correct for this one
    uint8_t     white;
    uint8_t     black;
    uint16_t    photo;
    uint16_t    sound;
    uint32_t    time_end;

    uint8_t     lineval;
}package;

int parse_package()
{
    package.type = package.buffer[1];
    uint8_t* rd_ptr = package.buffer + 2;

    switch (package.type) {
        case START:
            break;
        case STOP:
            break;
        case HEADER:
            package.buffer[package.size] = '\0';
            break;
        case SAMPLE:
            memcpy(&package.time, rd_ptr, sizeof(package.time));
            rd_ptr += sizeof(package.time);
            memcpy(&package.white, rd_ptr, sizeof(package.white));
            rd_ptr += sizeof(package.white);
            memcpy(&package.black, rd_ptr, sizeof(package.black));
            rd_ptr += sizeof(package.black);
            memcpy(&package.photo, rd_ptr, sizeof(package.photo));
            rd_ptr += sizeof(package.photo);
            memcpy(&package.sound, rd_ptr, sizeof(package.sound));
            rd_ptr += sizeof(package.sound);
            break;
        case SCREEN_INTERRUPT:
            memcpy(&package.time, rd_ptr, sizeof(package.time));
            rd_ptr += sizeof(package.time);
            memcpy(&package.lineval, rd_ptr, sizeof(package.lineval));
            rd_ptr += sizeof(package.lineval);
            break;
        case SOUND_SAMPLE:
            memcpy(&package.time, rd_ptr, sizeof(package.time));
            rd_ptr += sizeof(package.time);
            memcpy(&package.time_end, rd_ptr, sizeof(package.time_end));
            rd_ptr += sizeof(package.time_end);
            break;
        default:
            return -1;
    }
    return 0;
}

int read_package(TeensyDevice* teensy) {
    int nread; // num bytes read from last read.
    int nb_tot_read = 0;

    nread = teensy_read(teensy,(char*) package.buffer, 1);
    if (nread < 0)
        return nread;
    nb_tot_read++;
    package.size = package.buffer[0];

    while(nb_tot_read < package.size) {

        nread = teensy_read(teensy,
                            (char*)package.buffer + nb_tot_read,
                            package.size - nb_tot_read);

        nb_tot_read += nread;
    }
    return nb_tot_read;
}

int parse_cmd_options(int argc, char**argv)
{
    int ret;
    option_context* options = NULL;

    ret = options_parse(&options,
                        argc,
                        argv,
                        arguments,
                        sizeof(arguments)/sizeof(arguments[0]));
    if (ret) {
        fprintf(stderr, "Unable to parse the commandline options\n");
        exit(EXIT_FAILURE);
    }
    
    if (option_context_have_option(options, "help")) {
        // TODO print usage.
        exit(EXIT_SUCCESS);
    }

    if (option_context_have_option(options, "device")) {
        const char* device_name = NULL;
        ret = option_context_str_value(options, "device", &device_name);
        if (ret) {
            fprintf(
                stderr,
                "Unexpected error while parsing argument for device name\n"
                );
            exit(EXIT_FAILURE);
        }
        snprintf(device, sizeof(device), "%s", device_name);
    }

    if (option_context_have_option(options, "output-filename")) {
        const char* output_name = NULL;
        ret = option_context_str_value(options,
                                       "output-filename",
                                       &output_name);
        if (ret) {
            fprintf(
                stderr,
                "Unexpected error while parsing argument for output name\n"
            );
            exit(EXIT_FAILURE);
        }
        snprintf(output_fn, sizeof(output_fn), "%s", output_name);
    }
    
    return ret;
}

int main(int argc, char** argv) {
    int ret;
    //struct termios in, out;
    TeensyDevice* teensy = NULL;
    FILE* output = NULL;

    if (parse_cmd_options(argc, argv)) {
        fprintf(stderr, "Unable to parse commandline options.\n");
        return -1;
    }

    output = fopen(output_fn, "w");
    if (!output) {
        char buf[1024];
        snprintf(buf, sizeof(buf), "Unable to open %s", output_fn);
        perror(buf);
    }

    signal(SIGINT, signal_handler);

    teensy = teensy_new();
    if (!teensy) {
        perror("Unable to create a teensy device");
        return EXIT_FAILURE;
    }
    
    ret = teensy_open(teensy, device);
    if (ret) {
        perror("Unable to open teensy device");
        return EXIT_FAILURE;
    }

    while(!interrupted && !stop) {

        ret = read_package(teensy);

        if (ret < 0) {
            perror("Unable to read package");
            break;
        }

        if (ret == 0 && verbose)
            fprintf(stderr, "time out\n");

        if (parse_package() < 0) {
            fprintf(stderr, "Unable to parse package\n");
            break;
        }
        switch(package.type) {
            case SAMPLE:
                printf("%u\t%d\t%d\t%d\t%d\n",
                        package.time,
                        package.white,
                        package.black,
                        package.photo,
                        package.sound
                       );
                break;
            case STOP:
                stop = 1;
                break;
            case START:
                break;
            case HEADER:
                printf("%s\n", &package.buffer[0] + 2);
                break;
            case SCREEN_INTERRUPT:
                fprintf(output, "%d\t%u\t%d\n",
                        SCREEN_INTERRUPT,
                        package.time,
                        package.lineval
                        );
                break;
            case SOUND_SAMPLE:
                fprintf(output, "%d\t%u\t%u\n",
                        SOUND_SAMPLE,
                        package.time,
                        package.time_end
                        );
                break;
            default:
                // We should always get a valid package(in theory)
                assert(0 == 1);
        }
    }

    teensy_close(teensy);

    fclose(output);
    return 0;
}
