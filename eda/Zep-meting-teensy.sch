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
L +5V #PWR01
U 1 1 59254CF6
P 950 950
F 0 "#PWR01" H 950 800 50  0001 C CNN
F 1 "+5V" H 950 1090 50  0000 C CNN
F 2 "" H 950 950 50  0000 C CNN
F 3 "" H 950 950 50  0000 C CNN
	1    950  950 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 59254D0A
P 950 1650
F 0 "#PWR02" H 950 1400 50  0001 C CNN
F 1 "GND" H 950 1500 50  0000 C CNN
F 2 "" H 950 1650 50  0000 C CNN
F 3 "" H 950 1650 50  0000 C CNN
	1    950  1650
	1    0    0    -1  
$EndComp
Text Label 1550 950  0    60   ~ 0
VCC
$Comp
L PWR_FLAG #FLG03
U 1 1 59254D27
P 1550 1650
F 0 "#FLG03" H 1550 1745 50  0001 C CNN
F 1 "PWR_FLAG" H 1550 1830 50  0000 C CNN
F 2 "" H 1550 1650 50  0000 C CNN
F 3 "" H 1550 1650 50  0000 C CNN
	1    1550 1650
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
L +5V #PWR04
U 1 1 59315084
P 9950 3550
F 0 "#PWR04" H 9950 3400 50  0001 C CNN
F 1 "+5V" H 9950 3690 50  0000 C CNN
F 2 "" H 9950 3550 50  0000 C CNN
F 3 "" H 9950 3550 50  0000 C CNN
	1    9950 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 593150A4
P 9950 2100
F 0 "#PWR05" H 9950 1850 50  0001 C CNN
F 1 "GND" H 9950 1950 50  0000 C CNN
F 2 "" H 9950 2100 50  0000 C CNN
F 3 "" H 9950 2100 50  0000 C CNN
	1    9950 2100
	1    0    0    -1  
$EndComp
$Comp
L BeexyBox_B U4
U 1 1 593151FF
P 9050 4600
F 0 "U4" H 9050 3950 60  0000 C CNN
F 1 "BeexyBox_B" H 9050 5250 60  0000 C CNN
F 2 "" H 9050 4650 60  0000 C CNN
F 3 "" H 9050 4650 60  0000 C CNN
	1    9050 4600
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR06
U 1 1 5931526D
P 8350 4000
F 0 "#PWR06" H 8350 3750 50  0001 C CNN
F 1 "GND" H 8350 3850 50  0000 C CNN
F 2 "" H 8350 4000 50  0000 C CNN
F 3 "" H 8350 4000 50  0000 C CNN
	1    8350 4000
	1    0    0    -1  
$EndComp
NoConn ~ 8950 4150
NoConn ~ 9050 4150
NoConn ~ 9150 4150
NoConn ~ 9350 4150
NoConn ~ 9450 4150
NoConn ~ 9550 4150
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
$Comp
L BC547 Q1
U 1 1 593153D3
P 6250 1850
F 0 "Q1" H 6450 1925 50  0000 L CNN
F 1 "BC547" H 6450 1850 50  0000 L CNN
F 2 "TO-92" H 6450 1775 50  0000 L CIN
F 3 "" H 6250 1850 50  0000 L CNN
	1    6250 1850
	1    0    0    -1  
$EndComp
$Comp
L TEMT6000_sparkfun U2
U 1 1 5931546A
P 4700 1850
F 0 "U2" H 4700 1650 60  0000 C CNN
F 1 "TEMT6000_sparkfun" H 4700 2100 60  0000 C CNN
F 2 "" H 4650 2200 60  0000 C CNN
F 3 "" H 4650 2200 60  0000 C CNN
	1    4700 1850
	1    0    0    1   
$EndComp
$Comp
L R R4
U 1 1 593154BC
P 6350 1300
F 0 "R4" V 6430 1300 50  0000 C CNN
F 1 "10k" V 6350 1300 50  0000 C CNN
F 2 "" V 6280 1300 50  0000 C CNN
F 3 "" H 6350 1300 50  0000 C CNN
	1    6350 1300
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 593154FE
P 5650 1850
F 0 "R3" V 5730 1850 50  0000 C CNN
F 1 "10k" V 5650 1850 50  0000 C CNN
F 2 "" V 5580 1850 50  0000 C CNN
F 3 "" H 5650 1850 50  0000 C CNN
	1    5650 1850
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 59315722
P 5400 1400
F 0 "R2" V 5480 1400 50  0000 C CNN
F 1 "47k" V 5400 1400 50  0000 C CNN
F 2 "" V 5330 1400 50  0000 C CNN
F 3 "" H 5400 1400 50  0000 C CNN
	1    5400 1400
	-1   0    0    1   
$EndComp
Text Label 4300 1050 0    60   ~ 0
VCC
$Comp
L GND #PWR07
U 1 1 59315830
P 4300 2400
F 0 "#PWR07" H 4300 2150 50  0001 C CNN
F 1 "GND" H 4300 2250 50  0000 C CNN
F 2 "" H 4300 2400 50  0000 C CNN
F 3 "" H 4300 2400 50  0000 C CNN
	1    4300 2400
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 59315967
P 6750 1550
F 0 "R5" V 6830 1550 50  0000 C CNN
F 1 "1k" V 6750 1550 50  0000 C CNN
F 2 "" V 6680 1550 50  0000 C CNN
F 3 "" H 6750 1550 50  0000 C CNN
	1    6750 1550
	0    1    1    0   
$EndComp
Text Label 8600 1750 0    60   ~ 0
SCREEN_PIN
Text Label 7100 1550 0    60   ~ 0
SCREEN_PIN
Text Label 8600 1500 0    60   ~ 0
SOUND_LEVEL_PIN
$Comp
L CONN_01X03 P1
U 1 1 593161FE
P 4300 3300
F 0 "P1" H 4300 3500 50  0000 C CNN
F 1 "CONN_01X03" V 4400 3300 50  0000 C CNN
F 2 "" H 4300 3300 50  0000 C CNN
F 3 "" H 4300 3300 50  0000 C CNN
	1    4300 3300
	-1   0    0    -1  
$EndComp
Text Label 4850 3500 0    60   ~ 0
audio_gnd
Text Label 4850 3300 0    60   ~ 0
audio_right
Text Label 4850 3100 0    60   ~ 0
audio_left
$Comp
L GND #PWR08
U 1 1 5931661E
P 5400 3600
F 0 "#PWR08" H 5400 3350 50  0001 C CNN
F 1 "GND" H 5400 3450 50  0000 C CNN
F 2 "" H 5400 3600 50  0000 C CNN
F 3 "" H 5400 3600 50  0000 C CNN
	1    5400 3600
	1    0    0    -1  
$EndComp
Text Label 5800 3100 0    60   ~ 0
SOUND_LEVEL_PIN
Text Notes 4300 900  0    60   ~ 0
Display measurement circuit\n
Text Notes 4250 2950 0    60   ~ 0
Sound measurement circuit
Text Label 7350 3700 0    60   ~ 0
SENSOR_PHOTO_PIN
Text Label 7350 3850 0    60   ~ 0
SENSOR_SOUND_PIN
$Comp
L D D1
U 1 1 593175D9
P 4200 5200
F 0 "D1" H 4200 5300 50  0000 C CNN
F 1 "D" H 4200 5100 50  0000 C CNN
F 2 "" H 4200 5200 50  0000 C CNN
F 3 "" H 4200 5200 50  0000 C CNN
	1    4200 5200
	0    1    1    0   
$EndComp
$Comp
L GND #PWR09
U 1 1 59317642
P 4200 5550
F 0 "#PWR09" H 4200 5300 50  0001 C CNN
F 1 "GND" H 4200 5400 50  0000 C CNN
F 2 "" H 4200 5550 50  0000 C CNN
F 3 "" H 4200 5550 50  0000 C CNN
	1    4200 5550
	1    0    0    -1  
$EndComp
$Comp
L LM358N U1
U 1 1 59317688
P 5100 5000
F 0 "U1" H 5050 5200 50  0000 L CNN
F 1 "LM358N" H 5050 4750 50  0000 L CNN
F 2 "" H 5100 5000 50  0000 C CNN
F 3 "" H 5100 5000 50  0000 C CNN
	1    5100 5000
	1    0    0    1   
$EndComp
$Comp
L R R1
U 1 1 59317737
P 4750 4400
F 0 "R1" V 4830 4400 50  0000 C CNN
F 1 "1M" V 4750 4400 50  0000 C CNN
F 2 "" V 4680 4400 50  0000 C CNN
F 3 "" H 4750 4400 50  0000 C CNN
	1    4750 4400
	0    1    1    0   
$EndComp
$Comp
L GND #PWR010
U 1 1 5931780C
P 4600 5550
F 0 "#PWR010" H 4600 5300 50  0001 C CNN
F 1 "GND" H 4600 5400 50  0000 C CNN
F 2 "" H 4600 5550 50  0000 C CNN
F 3 "" H 4600 5550 50  0000 C CNN
	1    4600 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  1650 1550 1650
Wire Wire Line
	9500 3400 9500 3550
Wire Wire Line
	9500 3550 9950 3550
Wire Wire Line
	9500 2250 9500 2100
Wire Wire Line
	9500 2100 9950 2100
Wire Wire Line
	8550 4150 8550 4000
Wire Wire Line
	8550 4000 8350 4000
Wire Wire Line
	8650 4150 8650 3650
Wire Wire Line
	8650 3650 9200 3650
Wire Wire Line
	9200 3650 9200 3400
Wire Wire Line
	8750 4150 8750 3800
Wire Wire Line
	8750 3800 9100 3800
Wire Wire Line
	9100 3800 9100 3400
Wire Wire Line
	6350 2400 6350 2050
Wire Wire Line
	4300 2400 6350 2400
Wire Wire Line
	4300 1050 6350 1050
Wire Wire Line
	6350 1050 6350 1150
Wire Wire Line
	6350 1450 6350 1650
Wire Wire Line
	5800 1850 6050 1850
Wire Wire Line
	5000 1750 5000 1050
Connection ~ 5000 1050
Wire Wire Line
	5000 1850 5150 1850
Wire Wire Line
	5150 1850 5150 2400
Connection ~ 5150 2400
Wire Wire Line
	5400 1950 5000 1950
Wire Wire Line
	5400 1550 5400 1950
Connection ~ 5400 1850
Wire Wire Line
	5400 1250 5400 1050
Connection ~ 5400 1050
Wire Wire Line
	6350 1550 6600 1550
Connection ~ 6350 1550
Wire Wire Line
	5400 1850 5500 1850
Wire Wire Line
	8400 2250 8400 1750
Wire Wire Line
	8400 1750 8600 1750
Wire Wire Line
	6900 1550 7100 1550
Wire Wire Line
	8300 2250 8300 1500
Wire Wire Line
	8300 1500 8600 1500
Wire Wire Line
	4500 3400 4650 3400
Wire Wire Line
	4650 3400 4650 3500
Wire Wire Line
	4650 3500 5400 3500
Wire Wire Line
	5400 3500 5400 3600
Wire Wire Line
	5550 3300 4500 3300
Wire Wire Line
	4650 3100 5800 3100
Wire Wire Line
	5550 3100 5550 3300
Wire Wire Line
	4650 3100 4650 3200
Wire Wire Line
	4650 3200 4500 3200
Connection ~ 5550 3100
Wire Wire Line
	8300 3700 8300 3400
Wire Wire Line
	7350 3700 8300 3700
Wire Wire Line
	8400 3400 8400 3850
Wire Wire Line
	8400 3850 7350 3850
Wire Wire Line
	4800 5100 4600 5100
Wire Wire Line
	4600 5100 4600 5550
Text Label 5000 5500 0    60   ~ 0
VCC
Wire Wire Line
	5000 4700 5000 4500
Wire Wire Line
	5000 4500 5150 4500
$Comp
L GND #PWR011
U 1 1 593179DE
P 5150 4500
F 0 "#PWR011" H 5150 4250 50  0001 C CNN
F 1 "GND" H 5150 4350 50  0000 C CNN
F 2 "" H 5150 4500 50  0000 C CNN
F 3 "" H 5150 4500 50  0000 C CNN
	1    5150 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 5000 5850 5000
Wire Wire Line
	5600 5000 5600 4400
Wire Wire Line
	5600 4400 4900 4400
Connection ~ 5600 5000
Wire Wire Line
	4600 4400 4400 4400
Wire Wire Line
	4400 4400 4400 4900
Wire Wire Line
	4200 4900 4800 4900
Wire Wire Line
	4200 5050 4200 4900
Connection ~ 4400 4900
Text Label 5850 5000 0    60   ~ 0
SENSOR_PHOTO_PIN
Wire Wire Line
	4200 5550 4200 5350
Text Notes 4200 4300 0    60   ~ 0
Analog photo measurement circuit
Text Notes 4050 5300 1    60   ~ 0
Photo
Wire Wire Line
	5800 3100 5800 3300
Text Label 5800 3300 0    60   ~ 0
SENSOR_SOUND_PIN
Wire Wire Line
	5000 5500 5000 5300
$Comp
L PWR_FLAG #FLG012
U 1 1 5931E063
P 1250 950
F 0 "#FLG012" H 1250 1045 50  0001 C CNN
F 1 "PWR_FLAG" H 1250 1130 50  0000 C CNN
F 2 "" H 1250 950 50  0000 C CNN
F 3 "" H 1250 950 50  0000 C CNN
	1    1250 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  950  1550 950 
Connection ~ 1250 950 
NoConn ~ 8200 2250
$EndSCHEMATC
