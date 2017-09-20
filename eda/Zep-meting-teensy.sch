EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:zep
LIBS:Zep-meting-teensy-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L +5V #PWR2
U 1 1 59254CF6
P 1400 6350
F 0 "#PWR2" H 1400 6200 50  0001 C CNN
F 1 "+5V" H 1400 6490 50  0000 C CNN
F 2 "" H 1400 6350 50  0000 C CNN
F 3 "" H 1400 6350 50  0000 C CNN
	1    1400 6350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 59254D0A
P 1400 7050
F 0 "#PWR3" H 1400 6800 50  0001 C CNN
F 1 "GND" H 1400 6900 50  0000 C CNN
F 2 "" H 1400 7050 50  0000 C CNN
F 3 "" H 1400 7050 50  0000 C CNN
	1    1400 7050
	1    0    0    -1  
$EndComp
Text Label 2000 6350 0    60   ~ 0
VCC
$Comp
L PWR_FLAG #FLG2
U 1 1 59254D27
P 2000 7050
F 0 "#FLG2" H 2000 7145 50  0001 C CNN
F 1 "PWR_FLAG" H 2000 7230 50  0000 C CNN
F 2 "" H 2000 7050 50  0000 C CNN
F 3 "" H 2000 7050 50  0000 C CNN
	1    2000 7050
	1    0    0    -1  
$EndComp
$Comp
L Teensy3.2 U3
U 1 1 59315CD1
P 8850 2800
F 0 "U3" H 9150 1950 60  0000 C CNN
F 1 "Teensy3.2" H 8850 3600 60  0000 C CNN
F 2 "" H 8850 3050 60  0000 C CNN
F 3 "" H 8850 3050 60  0000 C CNN
	1    8850 2800
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR11
U 1 1 59315084
P 9950 3550
F 0 "#PWR11" H 9950 3400 50  0001 C CNN
F 1 "+5V" H 9950 3690 50  0000 C CNN
F 2 "" H 9950 3550 50  0000 C CNN
F 3 "" H 9950 3550 50  0000 C CNN
	1    9950 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR10
U 1 1 593150A4
P 9950 2100
F 0 "#PWR10" H 9950 1850 50  0001 C CNN
F 1 "GND" H 9950 1950 50  0000 C CNN
F 2 "" H 9950 2100 50  0000 C CNN
F 3 "" H 9950 2100 50  0000 C CNN
	1    9950 2100
	1    0    0    -1  
$EndComp
NoConn ~ 9300 3400
NoConn ~ 9400 3400
NoConn ~ 8500 2250
NoConn ~ 8600 2250
NoConn ~ 8700 2250
NoConn ~ 8800 2250
NoConn ~ 8900 2250
NoConn ~ 9000 2250
NoConn ~ 9100 2250
NoConn ~ 9200 2250
NoConn ~ 9300 2250
NoConn ~ 9400 2250
NoConn ~ 8200 3400
NoConn ~ 8500 3400
NoConn ~ 8600 3400
NoConn ~ 8700 3400
NoConn ~ 8800 3400
NoConn ~ 8900 3400
NoConn ~ 9000 3400
Text Label 8600 1750 0    60   ~ 0
SCREEN_PIN
Text Label 8600 1500 0    60   ~ 0
SOUND_LEVEL_PIN
$Comp
L CONN_01X03 P1
U 1 1 593161FE
P 3700 3950
F 0 "P1" H 3700 4150 50  0000 C CNN
F 1 "CONN_01X03" V 3800 3950 50  0000 C CNN
F 2 "" H 3700 3950 50  0000 C CNN
F 3 "" H 3700 3950 50  0000 C CNN
	1    3700 3950
	-1   0    0    -1  
$EndComp
Text Label 4250 4150 0    60   ~ 0
audio_gnd
Text Label 4250 3950 0    60   ~ 0
audio_right
Text Label 4250 3750 0    60   ~ 0
audio_left
$Comp
L GND #PWR8
U 1 1 5931661E
P 4800 4250
F 0 "#PWR8" H 4800 4000 50  0001 C CNN
F 1 "GND" H 4800 4100 50  0000 C CNN
F 2 "" H 4800 4250 50  0000 C CNN
F 3 "" H 4800 4250 50  0000 C CNN
	1    4800 4250
	1    0    0    -1  
$EndComp
Text Label 5200 3750 0    60   ~ 0
SOUND_LEVEL_PIN
Text Notes 3650 3600 0    60   ~ 0
Sound measurement circuit
$Comp
L D D1
U 1 1 593175D9
P 3800 6000
F 0 "D1" H 3800 6100 50  0000 C CNN
F 1 "D" H 3800 5900 50  0000 C CNN
F 2 "" H 3800 6000 50  0000 C CNN
F 3 "" H 3800 6000 50  0000 C CNN
	1    3800 6000
	0    1    1    0   
$EndComp
$Comp
L GND #PWR4
U 1 1 59317642
P 3800 6350
F 0 "#PWR4" H 3800 6100 50  0001 C CNN
F 1 "GND" H 3800 6200 50  0000 C CNN
F 2 "" H 3800 6350 50  0000 C CNN
F 3 "" H 3800 6350 50  0000 C CNN
	1    3800 6350
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 59317737
P 4350 5200
F 0 "R1" V 4430 5200 50  0000 C CNN
F 1 "1M" V 4350 5200 50  0000 C CNN
F 2 "" V 4280 5200 50  0000 C CNN
F 3 "" H 4350 5200 50  0000 C CNN
	1    4350 5200
	0    1    1    0   
$EndComp
$Comp
L GND #PWR6
U 1 1 5931780C
P 4200 6350
F 0 "#PWR6" H 4200 6100 50  0001 C CNN
F 1 "GND" H 4200 6200 50  0000 C CNN
F 2 "" H 4200 6350 50  0000 C CNN
F 3 "" H 4200 6350 50  0000 C CNN
	1    4200 6350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 7050 2000 7050
Wire Wire Line
	9500 3400 9500 3550
Wire Wire Line
	9500 3550 9950 3550
Wire Wire Line
	9500 2250 9500 2100
Wire Wire Line
	9500 2100 9950 2100
Wire Wire Line
	8400 2250 8400 1750
Wire Wire Line
	8400 1750 8600 1750
Wire Wire Line
	8300 2250 8300 1500
Wire Wire Line
	8300 1500 8600 1500
Wire Wire Line
	3900 4050 4050 4050
Wire Wire Line
	4050 4050 4050 4150
Wire Wire Line
	4050 4150 4800 4150
Wire Wire Line
	4800 4150 4800 4250
Wire Wire Line
	4050 3750 4050 3850
Wire Wire Line
	4050 3850 3900 3850
Wire Wire Line
	4400 5900 4200 5900
Wire Wire Line
	4200 5900 4200 6350
Text Label 4600 6300 0    60   ~ 0
VCC
Wire Wire Line
	4600 5500 4600 5300
Wire Wire Line
	4600 5300 4750 5300
$Comp
L GND #PWR7
U 1 1 593179DE
P 4750 5300
F 0 "#PWR7" H 4750 5050 50  0001 C CNN
F 1 "GND" H 4750 5150 50  0000 C CNN
F 2 "" H 4750 5300 50  0000 C CNN
F 3 "" H 4750 5300 50  0000 C CNN
	1    4750 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 5800 5450 5800
Wire Wire Line
	5200 5800 5200 5200
Wire Wire Line
	5200 5200 4500 5200
Connection ~ 5200 5800
Wire Wire Line
	4200 5200 4000 5200
Wire Wire Line
	4000 5200 4000 5700
Wire Wire Line
	3800 5700 4400 5700
Wire Wire Line
	3800 5850 3800 5700
Connection ~ 4000 5700
Text Label 5450 5800 0    60   ~ 0
SENSOR_PHOTO_PIN
Wire Wire Line
	3800 6350 3800 6150
Text Notes 3800 5100 0    60   ~ 0
Analog photo measurement circuit
Text Notes 3650 6100 1    60   ~ 0
Photo
Wire Wire Line
	4600 6300 4600 6100
$Comp
L PWR_FLAG #FLG1
U 1 1 5931E063
P 1700 6350
F 0 "#FLG1" H 1700 6445 50  0001 C CNN
F 1 "PWR_FLAG" H 1700 6530 50  0000 C CNN
F 2 "" H 1700 6350 50  0000 C CNN
F 3 "" H 1700 6350 50  0000 C CNN
	1    1700 6350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 6350 2000 6350
Connection ~ 1700 6350
NoConn ~ 8200 2250
$Comp
L POT RV1
U 1 1 594BBAEB
P 4450 2350
F 0 "RV1" H 4450 2270 50  0000 C CNN
F 1 "1k" H 4450 2350 50  0000 C CNN
F 2 "" H 4450 2350 50  0000 C CNN
F 3 "" H 4450 2350 50  0000 C CNN
	1    4450 2350
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 594BCB2D
P 5150 2100
F 0 "R7" V 5230 2100 50  0000 C CNN
F 1 "10k" V 5150 2100 50  0000 C CNN
F 2 "" V 5080 2100 50  0000 C CNN
F 3 "" H 5150 2100 50  0000 C CNN
	1    5150 2100
	0    1    1    0   
$EndComp
$Comp
L R R6
U 1 1 594BCC4C
P 4150 2500
F 0 "R6" V 4230 2500 50  0000 C CNN
F 1 "330" V 4150 2500 50  0000 C CNN
F 2 "" V 4080 2500 50  0000 C CNN
F 3 "" H 4150 2500 50  0000 C CNN
	1    4150 2500
	1    0    0    -1  
$EndComp
$Comp
L TEMT6000_sparkfun U5
U 1 1 594BCDC6
P 3900 1500
F 0 "U5" H 3900 1300 60  0000 C CNN
F 1 "TEMT6000_sparkfun" H 3900 1750 60  0000 C CNN
F 2 "" H 3850 1850 60  0000 C CNN
F 3 "" H 3850 1850 60  0000 C CNN
	1    3900 1500
	1    0    0    1   
$EndComp
Wire Wire Line
	4200 1600 4550 1600
Wire Wire Line
	4200 1400 4200 950 
Wire Wire Line
	3800 950  4750 950 
Text Label 3800 950  0    60   ~ 0
VCC
Wire Wire Line
	4750 950  4750 1400
Connection ~ 4200 950 
$Comp
L GND #PWR1
U 1 1 594BD15B
P 3800 2950
F 0 "#PWR1" H 3800 2700 50  0001 C CNN
F 1 "GND" H 3800 2800 50  0000 C CNN
F 2 "" H 3800 2950 50  0000 C CNN
F 3 "" H 3800 2950 50  0000 C CNN
	1    3800 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 2950 3800 2800
Wire Wire Line
	4450 1800 4550 1800
Wire Wire Line
	5150 1700 5750 1700
Text Label 5750 1700 0    60   ~ 0
SCREEN_PIN
Wire Wire Line
	3800 2800 4750 2800
Wire Wire Line
	4750 2800 4750 2000
Wire Wire Line
	4150 2800 4150 2650
Connection ~ 4150 2800
Wire Wire Line
	4150 2350 4300 2350
Wire Wire Line
	5300 2100 5500 2100
Wire Wire Line
	5500 2100 5500 1700
Connection ~ 5500 1700
Wire Wire Line
	5000 2100 4450 2100
Wire Wire Line
	4450 1800 4450 2200
Connection ~ 4450 2100
Wire Wire Line
	4200 1500 4350 1500
Wire Wire Line
	4350 1500 4350 1900
Wire Wire Line
	4350 1900 3950 1900
Wire Wire Line
	3950 1900 3950 2800
Connection ~ 3950 2800
Text Notes 3800 750  0    60   ~ 0
Display measurement circuit\nSignal High when display is on.
$Comp
L LM358N U6
U 1 1 594BCA64
P 4850 1700
F 0 "U6" H 4800 1900 50  0000 L CNN
F 1 "LM358N" H 4800 1450 50  0000 L CNN
F 2 "" H 4850 1700 50  0000 C CNN
F 3 "" H 4850 1700 50  0000 C CNN
	1    4850 1700
	1    0    0    -1  
$EndComp
$Comp
L LM358N U6
U 2 1 594BFA45
P 4700 5800
F 0 "U6" H 4650 6000 50  0000 L CNN
F 1 "LM358N" H 4650 5550 50  0000 L CNN
F 2 "" H 4700 5800 50  0000 C CNN
F 3 "" H 4700 5800 50  0000 C CNN
	2    4700 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 3950 4950 3950
NoConn ~ 4950 3950
$Comp
L R R?
U 1 1 59C2429A
P 4900 3750
F 0 "R?" V 4980 3750 50  0000 C CNN
F 1 "1k" V 4900 3750 50  0000 C CNN
F 2 "" V 4830 3750 50  0000 C CNN
F 3 "" H 4900 3750 50  0000 C CNN
	1    4900 3750
	0    1    1    0   
$EndComp
Wire Wire Line
	4050 3750 4750 3750
Wire Wire Line
	5050 3750 5200 3750
Wire Wire Line
	8400 3400 8400 3850
Wire Wire Line
	8300 3700 8300 3400
Wire Wire Line
	8400 3850 7350 3850
Wire Wire Line
	7350 3700 8300 3700
Text Label 7350 3850 0    60   ~ 0
SENSOR_SOUND_PIN
Text Label 7350 3700 0    60   ~ 0
SENSOR_PHOTO_PIN
Wire Wire Line
	5200 3750 5200 3950
Text Label 5200 3950 0    60   ~ 0
SENSOR_SOUND_PIN
NoConn ~ 4600 2350
NoConn ~ 9200 3400
NoConn ~ 9100 3400
$EndSCHEMATC
