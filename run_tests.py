#!/usr/bin/env python3

import argparse
import sys
#import subprocess 
import os
import os.path
from pathlib import Path
import platform

teensypath      = Path()
run_test_dir    = Path(sys.argv[0]).parent
test_dir        = run_test_dir.joinpath(Path("zep-scripts/"))
audio_test      = Path(test_dir, "test_audio0.zp")
monitor_test    = Path(test_dir, "test_monitor3.zp")
framerate       = 60
target_head     = 0
verbose         = False

skip_audio      = False;
skip_monitor    = False

#durations of stimuli
stimulus_durations  = [16+2/3, 50, 100, 200, 500, 1000]     #ms
stimulus_durations  = [i/1000 for i in stimulus_durations]  #seconds
# store the number of frames to be presented in a stimulus
nframes             = []

def create_zep_command(script, *script_options):
    '''
    constructs a commando for os.system()
    @param script the name of the script
    @param script_options the options/arguments for the script
    '''
    command = ""
    if platform.system().lower() == "windows":
        command = "zep {}".format(str(script))
    else:
        command = "zep-2.0 {}".format(str(script))
        
    for opt in script_options:
        command = "".join([command, " ", opt])
    return command

def create_zep_argument(name, value):
    arg = "--{}={}".format(name, str(value))
    return arg

def run_audio_tests():
    '''Runs the audio measurement tests.'''
    datadir = Path(os.path.abspath("./data"))
    unameinfo = platform.uname()
    for i in stimulus_durations:
        opersys = unameinfo[0]
        arch = unameinfo[4]
        fn = Path("audio" + str(int(i*1000)) + "-" + opersys + "-" + arch + ".txt")
        command = create_zep_command(
                    audio_test,
                    create_zep_argument("dev", teensypath),
                    create_zep_argument("isi", i*1000),
                    create_zep_argument("logfile", Path.joinpath(datadir, fn)),
                    "--verbose" if verbose else ""
                    )
        if verbose:
            print("running", command)
        status = os.system(command)
        if status != 0:
            return status
    return 0

def run_monitor_tests():
    '''Runs the monitor/video performance tests.'''
    datadir = Path(os.path.abspath("./data"))
    unameinfo = platform.uname()
    for i in nframes:
        opersys = unameinfo[0]
        arch = unameinfo[4]
        fn = Path("monitor" + str(int(i*(1.0/framerate)*1000)) + "-" + opersys + "-" + arch + ".txt")
        command = create_zep_command(
                    monitor_test,
                    create_zep_argument("dev", teensypath),
                    create_zep_argument("nframes", i),
                    create_zep_argument("logfile", Path.joinpath(datadir, fn)),
                    create_zep_argument("target-head", target_head),
                    "--verbose" if verbose else ""
                    )
        if verbose:
            print("running", command)
        status = os.system(command)
        if status != 0:
            return status
    return 0

def run_tests():
    '''runs all tests'''
    if not skip_audio:
        run_audio_tests()
    if not skip_monitor:
        run_monitor_tests()

def parse_cmd():
    '''parses command line options and sets global variables.'''
    global teensypath, skip_monitor, skip_audio,\
           nframes, framerate, target_head, verbose
    parser = argparse.ArgumentParser(formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument("-t",
                        "--teensy",
                        help="Specify COM or filename",
                        default="/dev/ttyACM0",
                        type=str
                        )
    parser.add_argument("--skip-audio",
                        action="store_true",
                        help="skip the audio tests."
                        )
    parser.add_argument("--skip-monitor",
                        action="store_true",
                        help="skip the monitor tests."
                        )
    parser.add_argument("-f", "--frame-rate",
                        type=int,
                        default=60,
                        help="skip the monitor tests."
                        )
    parser.add_argument("--target-head",
                        type=int,
                        default=0,
                        help="specify default target head for monitor test."
                        )
    parser.add_argument("-v", "--verbose",
                        action="store_true",
                        help="Specify for verbose output."
                        )

    args = parser.parse_args()
    if args.skip_audio:
        skip_audio = True
    if args.skip_monitor:
        skip_monitor = True
    if args.frame_rate:
        framerate = args.frame_rate
    if args.target_head:
        target_head = args.target_head
    if args.verbose:
        verbose = True

    nframes = [i/(1.0/framerate) for i in stimulus_durations]
    teensypath = Path(args.teensy)

if __name__ == "__main__":
    parse_cmd()
    run_tests()

