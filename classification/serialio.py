#!/usr/bin/python
import sys
import serial

f = open('myfile.txt', 'w')
serdev = '/dev/ttyACM0'
ser = serial.Serial(serdev)

for i in xrange(0, 100):
	message = ser.readline()
	print(message)
	f.write(message)


f.close()
