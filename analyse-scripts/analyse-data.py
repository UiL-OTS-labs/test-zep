#!/usr/bin/env python3
import numpy as np
import scipy as sp
import matplotlib
import argparse 
from sys import argv
matplotlib.use('Qt4Agg')
from matplotlib import pyplot as plt

SCREEN= 4 # "type" of the screen columns in data
SOUND = 5 # "type" of the sound columns

#
# Parsing arguments and option on command line.
#
argparser = argparse.ArgumentParser()

# add optional arguments
argparser.add_argument('-i', '--isi', help="specify the inter stimulus time(ms)",
    type=float, default=(16.0+2.0/3.0))
argparser.add_argument('-f', '--framerate', help="specify the framerate",
    type=float, default=60.0)
argparser.add_argument('-p', '--plot-data', help="plot the graphs.",
    action='store_true')

# add positional arguments one input file is mandatory.
argparser.add_argument('file', nargs=1, help="the file to analyze")

# parse the arguments.
args = argparser.parse_args()

fn = args.file[0]   # filename to analyze
fr = args.framerate # frame rate
fd = 1.0/fr         # frame duration
fd*= 1000           # convert fd to milliseconds
isi= args.isi       # inter stimulus time

# all data in 2D-matrix first
data = sp.genfromtxt(fn)

types = data[:,0]           # column that defines the type of the column
times1 = data[:,1]          # obtain times
times2 = data[:,2]          # obtain end times (audio only)
on_off = data[:,2]          # whether the signal is high or low (video only)
times1 = times1 / 1000.0    # convert to microseconds to milliseconds
times2 = times2 / 1000.0    

# filter out all not screen times
screen_times = times1[types == SCREEN]
# filter sounds
sound_starts = times1[types == SOUND]
sound_ends   = times2[types == SOUND]

# Zero in line values transistor collector pin is low.
# Thus the transistor is conducting which means the output from the 
# light sensor is high, hence the transition was from dark to light.
# a 1 means the transistor isn't conducting which means there isn't much
# light falling on the light transistor.
line_values = data[:,1]
# Filter screen values.
line_values = line_values[types ==  SCREEN]

sound_axis = None
screen_axis= None
print ("args.plotdata\t", args.plot_data);

if len(screen_times) > 0:
    # The time between on or off-set of the screen.
    diff_times = sp.diff(screen_times)

    mean = sp.mean(diff_times)
    std  = sp.std(diff_times)
    print ("Mean transition time is: " + str(mean) )
    print ("Standard deviation: " + str(sp.std(diff_times)) )
    missed_frames    = sp.sum( diff_times > (isi + fd) )
    short_frames     = sp.sum( diff_times < (isi - fd) )

    print("Missed frames = " + str(missed_frames))
    print("Short frames  = " + str(short_frames))
    if args.plot_data:
        nbins = 100 
        blue = 'blue'
        red =  'red'
        lable_on = 'on'
        lable_off= 'off'
        colors=[blue, red]
        lables = [lable_on, lable_off] 
        off = np.array(diff_times[on_off[1:] == 1])
        on  = np.array(diff_times[on_off[1:] == 0])
        plt.hist([off, on], nbins, color=colors, label=lables)
        plt.legend(prop={'size': 10})

if len(sound_starts) > 0 and len(sound_ends) > 0:

    # stats about sound duration
    duration = sound_ends - sound_starts
    mean = sp.mean(duration);
    std = sp.std(duration);
    print("mean sound duration = {} ms".format(mean))
    print("mean sound duration standard deviation = {} ms".format(std))
    if(args.plot_data):
        sound_axis = plt.figure();
        plt.subplot(211)
        plt.xlabel("duration (ms)")
        plt.hist(duration, 25)

    # stats about sound onset isi's
    isi = sound_starts[1:len(sound_starts)] - sound_ends[0:len(sound_ends)-1] 
    mean= sp.mean(isi)
    std = sp.std(isi)
    print("mean sound isi = {} ms".format(mean))
    print("mean sound isi standard deviation = {} ms".format(std))
    if(args.plot_data):
        plt.subplot(212)
        plt.xlabel("isi (ms)")
        plt.hist(isi, 25)

if args.plot_data:
    plt.show();
