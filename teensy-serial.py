#!/usr/bin/env python
import serial
import time;
import sys;

serialdevice = '/dev/ttyACM0'
if len(sys.argv) > 1:
    serialdevice = sys.argv[1]

dev = serial.Serial(serialdevice, baudrate=10000000)
#Discard rubbish inside the buffer.
dev.reset_input_buffer()
dev.reset_output_buffer()
dev.write("start\n")

t1 = time.clock();

# measure for about 5s
try:
    while (t1 + 5) > time.clock():
        s = dev.readline()
        if s:
            print s,
except KeyboardInterrupt:
    pass

dev.write("stop\n")
