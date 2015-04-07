#!/usr/bin/python
import sys
import serial

f = open('myfile.txt', 'w')
serdev = '/dev/ttyACM0'
ser = serial.Serial(serdev)

ser.write("start\r\n")

while True:
	try:
		message = ser.readline()
		print(message)
		f.write(message)
	except:
		print "fail"

f.close()
