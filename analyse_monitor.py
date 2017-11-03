#!/usr/bin/env python3

import argparse as a
import csv
import sys
import numpy as np
import math

framedur = int(round(16.0e6 + 2e6/3.0e6))

def parseFileContents(f):
    '''
    Parses contents of already opened file f
    This function assumes, f is a tab separated csv file with on the
    first line a header. In the column are the timestamps were spp went high,
    the spp wen low, the monitor went on and of respectively.

    returns tuple with spp_on, spp_off, display on and off times
    '''
    with open(f, "r") as csvfile:
        lines = csvfile.readlines()
        lines = lines[1:] #skip header
        csvreader = csv.reader (lines, delimiter="\t")
        spp_on = []
        spp_off= []
        disp_on= []
        disp_off=[]
        for row in csvreader:
            if row[0]:
                spp_on.append(float(row[0]))
            if row[1]:
                spp_off.append(float(row[1]))
            if row[2]:
                disp_on.append(float(row[2]))
            if row[3]:
                disp_off.append(float(row[3]))
        return spp_on, spp_off, disp_on, disp_off

def process(fn):
    global framedur
    data    = parseFileContents(fn)

    spp_on  = np.array( data[0] )
    spp_off = np.array( data[1] )
    disp_on = np.array( data[2] )
    disp_off= np.array( data[3] )
    if len(spp_on) == 0 or len(spp_on) != len(spp_off):
        raise RuntimeError(
                "The spp onsets and ofsets (first two columns) are not valid."
                )
    if len(disp_on) == 0 or len(disp_off) == 0:
        raise RuntimeError(
                "Missing display on- and/or offset column(s)."
                )
    
    # Calculate mean spp, it to approximate the stimulus duration.
    diff_spp = spp_off - spp_on
    mean_spp = diff_spp.mean()
    if mean_spp < 0:
        diff_spp = spp_on - spp_off
        mean_spp = diff_spp.mean()

    print("Assumed stimulus duration = {}ms".format(mean_spp/1000))

    display_times = np.append(disp_on, disp_off)
    display_times.sort()

    good_trials = 0 # trials where the stimulus was presented on time
    short_frames= 0 # number of vsyncs the stimulus was presented to early
    long_frames = 0 # number of vsyncs the stimulus was presented to late.
    
    # the times between the presentation of 2 stimuli.
    stimdiffs = np.diff(display_times)

    for i in stimdiffs:
        time_discrepancy = i - mean_spp
        nframes = int(round((time_discrepancy) / framedur))
        if nframes == 0:
            good_trials     += 1
        elif nframes < 0:
            short_frames    += -nframes
        else:
            long_frames     += nframes
    print("n good trials = ", good_trials)
    print("n too early vblanks = ", short_frames)
    print("n too late  vblanks = ", long_frames)

def main():
    global framedur
    parser = a.ArgumentParser()
    parser.add_argument("files", nargs='+', help="The input files to process.")
    # note is converted to µs.
    parser.add_argument("-d", "--framedur", type=float, default=framedur,
                        help="The length of one frame in ms.")

    pa = parser.parse_args();
    if pa.framedur: 
        #convert to ms
        framedur = pa.framedur / 1e3
   
    files = pa.files
    for i in files:
        process(i)


if __name__ == "__main__":
    main()
