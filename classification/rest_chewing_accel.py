#!/usr/bin/python
import sys
import serial
import time

if(len(sys.argv) != 2):
	print 'Usage: python rest_chewing_accel.py <output file>'
	sys.exit(0)

f = open(sys.argv[1], 'w')
serdev = '/dev/ttyACM0'
ser = serial.Serial(serdev)

count = 0
print 'rest your jaw, collection starts in 2s'
time.sleep(2)
print 'Collecting data now('
for i in xrange(0, 2000):
	message = ser.readline()
	if(count == 0):
		count += 1
		continue
	f.write('0, ' + message)

print 'start chewing, collection starts in 2s'
time.sleep(2)
print 'Collecting data now'
for i in xrange(0, 2000):
	message = ser.readline()
	f.write('1, ' + message)

f.close()