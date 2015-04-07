import serial
serdev = '/dev/ttyACM1'
ser = serial.Serial(serdev, 9600)

f = open("start_test.txt", 'w')

ser.write("start\r\n")
while True:
	try:
		message = ser.read(16)
		print message
		f.write('0, ' + message)
	except:
		print "fail"