#!/usr/bin/env python3
import numpy as np
import scipy as sp
import matplotlib
import sys
from sys import argv
matplotlib.use('Qt4Agg')
from matplotlib import pyplot as plt

def print_usage(exit=False):
    print(sys.argv[0] + " " + "<name of input file>")

fn = ""
try:
    fn = sys.argv[1];
except IndexError as e:
    print_usage(True)
    exit(0)

#all data in 2D-matrix
data = sp.genfromtxt(fn)

# The times
times   = data[:,0]
w       = data[:,1]
b       = data[:,2]
photo   = data[:,3]
sound   = data[:,4]

photo_axes = plt.subplot(211)
photo_axes.plot(times/1e3, photo, 'go')

sound_axes = plt.subplot(212)
sound_axes.plot(times / 1e3, sound, 'r-')

plt.show()
