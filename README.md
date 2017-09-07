# test-zep
A number of files/programs that belong to te article about ZEP.

The purpose of this article is to get a publication in a peer reviewed article. We 
Hope that this creates extra some extra momentum for Zep. There are many tools
one can use to create psychological/psycholinguistic experiments. Zep is special
to those, because it is a relatively simple language to master and does the very
difficult stuff under the hood. All files in this repository Fall under the GPL-2.0
open source software licence, for details see the LICENSE file at the root directory.

The articile aims to present Zep major version 2.0. Hence, the scripts in this repository
should be run with zep-2.x .

# Directory structure
The build tree has a number of directories with different purposes.
## eda
This directory contains some helper files to create electronic schematics of the
experiment setup. This presents an overview of how the different electronic connections
should be made.
## firware
This directory contains the firmware used to do the measuring with a teensy device. More
information about Teensy devices can be found at: https://www.pjrc.com/teensy/ . In short
a teensy device is a ARM-Cortex M4 development board. This allows us to time changes on
electronic sensors in a realtime fashion.
## utils (deprecated)
This directory contains small utilities used internally to help ourselves.
## zep-scripts
This folder contains 2 scripts in these scripts these script generate the data presented in
the article. These scripts use the zep teensy plugin to communicate with the teensy device.

When Zep connects with a teensy device, the device resets its time to 0, every x µs the timestamp
is increased. Currently x = 10µs. Zep only gets events about electronic sensor events and
cannot adjust the timing. Each event has a teensy timestamp, a pin value and the logical readout
value of such pin. This makes the teensy an objective time measure tool.
