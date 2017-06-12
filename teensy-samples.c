
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <signal.h>
#include <poll.h>
#include <stdint.h>
#include <assert.h>
#include <getopt.h>

char device[1024]       = "/dev/ttyACM0";
char output_fn[1024]    = "./screen-output.txt";

const char* optstr = "d:o:";

volatile int interrupted = 0;
int stop = 0;

int verbose = 0;

void signal_handler(int signal) {
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

int read_package(int fd) {
    int ret;
    int nread; // num bytes read from last read.
    int poll_ms = 1000;
    int nb_tot_read = 0;

    struct pollfd p;
    p.fd = fd;
    p.events = POLLIN;

    ret = poll(&p, 1, poll_ms);

    // timeout
    if (ret <= 0)
        return 0;

    if (p.revents & POLLIN) {
        nread = read(fd, package.buffer, 1);
        if (nread < 0)
            return nread;
        nb_tot_read++;
        package.size = package.buffer[0];
    }
    if (p.revents & POLLHUP) {
        fprintf(stderr,  "Teensy hanged up.\n");
        return -1;
    }

    while(nb_tot_read < package.size) {
        ret = poll(&p, 1, poll_ms);
        if (ret < 0)
            return ret;

        nread = read(fd,
                     package.buffer + nb_tot_read,
                     package.size - nb_tot_read
                );

        nb_tot_read += nread;
    }
    return nb_tot_read;
}

int parse_cmd_options(int argc, char**argv)
{
    int c;
    while ((c = getopt(argc, argv, optstr)) > 0) {
        switch (c){
            case 'd':
                snprintf(device, sizeof(device), "%s", optarg);
                break;
            case 'o':
                snprintf(output_fn, sizeof(output_fn), "%s", optarg);
                break;
            default:
                return -1;
        }
    }
    return 0;
}

int main(int argc, char** argv) {
    int fd, ret;
    struct termios in, out;
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

    fd = open(device, O_RDWR | O_TRUNC | O_NOCTTY | O_NONBLOCK);
    if (fd < 0) {
        perror("Unable to open device");
        return 1;
    }

    ret = tcgetattr(fd, &in);
    if (ret != 0) {
        perror("Unable to get terminal settings");
        return 1;
    }

    cfmakeraw(&out);
    ret = tcsetattr(fd, TCSANOW, &out);
    if (ret != 0) {
        perror("Unable to set proper raw terminal settings");
        return 1;
    }

    // clear the buffers
    ret = tcflush(fd, TCIOFLUSH);
    if (ret != 0) {
        perror("Unable to set flush terminal before use.");
        return 1;
    }
    fprintf (stderr, "Flushed buffers.\n");

    while(!interrupted && !stop) {

        ret = read_package(fd);

        if (ret < 0) {
            perror("Unable to read package");
            break;
        }
        if (ret == 0) {
            if (verbose)
                fprintf(stderr, "time out\n");
            continue;
        }

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

    // reset terminal settings.
    tcsetattr(fd,TCSAFLUSH, &in);

    close(fd);
    fclose(output);
    return 0;
}
