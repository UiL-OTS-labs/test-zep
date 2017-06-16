#!/bin/bash

TEENSY_SAMPLES= 

# Run one test with zep in the background and Teensy monitor in the foreground
# takes one argument, the number of frames per stimulus.
function run_video_test {
    ./teensy-samples -d $TEENSY_DEVICE -o "video_output$1.txt" > "video_analog_out$1.txt" &
    zep-2.0 zep-scripts/test_monitor3 --nframes=$1
    wait $!
}

# Run one test with zep in the background and Teensy monitor in the foreground
function run_audio_test {
    ./teensy-samples -d $TEENSY_DEVICE -o "audio_output$1.txt" > "audio_analog_out$1.txt" &
    zep-2.0 zep-scripts/test_audio0 --isi=$1 --hwlatency=${HW_LATENCY}
    wait $!
}

# takes program name as argument
function print_usage() {
    printf "Usage %s: [-l hardware_latency] [-a] [-v]" $0
    echo -e "\n"
    echo -e "\t-l specify hardware_latency for sound test eg 3.3ms."
    echo -e "\t-a skip sound test."
    echo -e "\t-v skip video test."
}

TEENSY_DEVICE="/dev/ttyACM1"
HW_LATENCY="0.0ms"


if [ -z $TEENSY ];
then
    TEENSY_DEVICE="${TEENSY}"
fi

if [ -z $HARDWARE_LATENCY ];
then
    HW_LATENCY=${HARDWARE_LATENCY}
fi

skip_audio=
skip_video=

while getopts "l:avht:" name ; do
  case $name in
    l)
      HW_LATENCY=$OPTARG
      ;;
    a)
      skip_audio=1
      ;;
    h)
      print_usage $0
      exit 0
      ;;
    t)
      TEENSY_DEVICE=${OPTARG}
      ;;
    v)
      skip_video=1
      ;;
    \?)
      print_usage $0
      exit 1
      ;;
    :)
      print_usage $0
      exit 1
      ;;
  esac
done

probe="./Release/teensy-samples"
if [ -x $probe ]; then
    TEENSY_SAMPLES=$probe
fi

probe="./Debug/teensy-samples"
if [ -x $probe ]; then
    TEENSY_SAMPLES=$probe
fi

if [ -z $TEENSY_SAMPLES ]; then
    echo "Unable to find the teensy-samples program did you build it?" 1>&2
    exit 1
fi

if [ ! $skip_video ]; then
    # run all video tests.
    for i in 1 3 6 12 30 60
    do
        echo "Running test with $i frames per stimulus."
        run_video_test $i
    done
fi

if [ ! $skip_audio ]; then
    # Run the audio tests
    # Let use 17 ms instead of 16.6667 Since, we use a frequency of
    # 10 KHz. Then a period will be completed precisely.
    for i in 17 50 100 200 500 1000
    do
        echo "Running audio test with an isi of ${i} and hw-latency ${HW_LATENCY}."
        run_audio_test $i $HW_LATENCY
    done
fi
