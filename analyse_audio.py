#!/usr/bin/env python3

import numpy as np
import argparse as a
from os.path import basename

def process(fn):
    data = np.genfromtxt(fn, skip_header=1)
    
    # get columns and convert from µs to ms
    spp_start   = data[:,0] / 1000
    spp_end     = data[:,1] / 1000
    snd_start   = data[:,2] / 1000
    snd_end     = data[:,3] / 1000

    diff_spp                = spp_end - spp_start
    diff_snd                = snd_end - snd_start
    offset_snd_start        = snd_start - spp_start
    offset_snd_end          = snd_end   - spp_end

    mean_diff_spp           = np.mean(diff_spp)
    mean_diff_snd           = np.mean(diff_snd)
    mean_offset_snd_start   = np.mean(offset_snd_start)
    mean_offset_snd_end     = np.mean(offset_snd_end)
    
    std_diff_spp            = np.std(diff_spp)
    std_diff_snd            = np.std(diff_snd)
    std_offset_snd_start    = np.std(offset_snd_start)
    std_offset_snd_end      = np.std(offset_snd_end)
    
    min_diff_spp            = np.min(diff_spp)
    min_diff_snd            = np.min(diff_snd)
    min_offset_snd_start    = np.min(offset_snd_start)
    min_offset_snd_end      = np.min(offset_snd_end)
    
    max_diff_spp            = np.max(diff_spp)
    max_diff_snd            = np.max(diff_snd)
    max_offset_snd_start    = np.max(offset_snd_start)
    max_offset_snd_end      = np.max(offset_snd_end)

    print("Summarizing statistics for {}".format(basename(fn)))
    print("\t{}\t{}\t{}\t{}".format(
            "spp_dur",
            "snd_dur",
            "offset_snd_on",
            "offset_snd_off")
            )
    print("mean\t{:.3f}\t{:.3f}\t{:.3f}\t{:.3f}".format(
            mean_diff_spp,
            mean_diff_snd,
            mean_offset_snd_start,
            mean_offset_snd_end )
            )
    print("std\t{:.3f}\t{:.3f}\t{:.3f}\t{:.3f}".format(
            std_diff_spp,
            std_diff_snd,
            std_offset_snd_start,
            std_offset_snd_end )
            )
    print("min\t{:.3f}\t{:.3f}\t{:.3f}\t{:.3f}".format(
            min_diff_spp,
            min_diff_snd,
            min_offset_snd_start,
            min_offset_snd_end )
            )
    print("max\t{:.3f}\t{:.3f}\t{:.3f}\t{:.3f}".format(
            max_diff_spp,
            max_diff_snd,
            max_offset_snd_start,
            max_offset_snd_end )
            )
    # a blank line to separate output between files.
    print()
                

def main():
    parser = a.ArgumentParser()
    parser.add_argument("files",nargs='+', help="The input files to process.")

    pa = parser.parse_args();
    files = pa.files
    for i in files:
        process(i)

if __name__ == "__main__":
    main();

