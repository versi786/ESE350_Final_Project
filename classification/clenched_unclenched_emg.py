#!/usr/bin/python
import sys
import serial
import time

if(len(sys.argv) != 2):
	print 'Usage: python clenched_unclenched_serial.py <output file>'
	sys.exit(0)

f = open(sys.argv[1], 'w')
serdev = '/dev/ttyACM1'
ser = serial.Serial(serdev)

print 'rest your jaw, collection starts in 2s'
time.sleep(2)
print 'Collecting data now'
ser.write("start\r\n")
# print "start"
# time.sleep(4)
# print "end"
count = 0;
while True:
	try:
		message = ser.readline()
		print i
		int(message)
		f.write('0, ' + message)
		count += 1
		if(count == 3000):
			break
	except:
		print "fail"
		t = 0

print 'clench your jaw, collection starts in 2s'
time.sleep(2)
print 'Collecting data now'
ser.write("start\r\n")

count = 0;
while True:
	try:
		message = ser.readline()
		print i
		int(message)
		f.write('1, ' + message)
		count += 1
		if(count == 3000):
			break
	except:
		t = 0
# for i in xrange(0, 3000):
# 	message = ser.readline()
# 	try:
# 		int(message)
# 		f.write('0, ' + message)
# 	except:
# 		t = 0

f.close()
