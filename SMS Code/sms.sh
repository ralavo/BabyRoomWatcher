#!/bin/sh

DEV=/dev/ttyS0
DESTNUM="5744040341"
SMS="Motion was Detected\nTemperature is $1C\n Humidity is $2% \n Light is $3"

echo  "AT\r" > $DEV
sleep 1
echo  "AT+CMGF=1\r" > $DEV
sleep 1
echo  "AT+CMGS=\"$DESTNUM\"\r" > $DEV
sleep 1
echo  "$SMS\032" > $DEV 
