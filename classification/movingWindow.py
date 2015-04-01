#!/usr/bin/python
import sys
import serial

length = 60
sampFreq = 10
winSize = 3
winDisplacement = 1.5

def numWindows(dataLength, sampFreq, winLen, winDisplacement):
	numWindows = ((((dataLength/sampFreq)- winLen)/winDisplacement) + 1)
	return numWindows

def MWF(data, dataLength, sampFreq, winLen, winDisplacement, func):
	l = []
	nw = numWindows(dataLength, sampFreq, winLen, winDisplacement)
	x = 0
	for j in xrange(0, nw):
		l.append(func(data[x:x + winLen]))
		x += winDisplacement
	return l

#nothing
def make_nothing():
	return lambda x: x

#Max
def make_max():
	return lambda x: max(x)

#Min
def make_min():
	return lambda x: min(x)

#range
def make_range():
	return lambda x: max(x) - min(x)

#


data = [1,2,3,4,5,6]
sampFreq = 1
winLen = 3
winDisplacement = 1

nothing_func = make_nothing()
nothingList = MWF(data, len(data), sampFreq, winLen, winDisplacement, nothing_func)
print 'nothing: ', nothingList


max_func = make_max()
maxList = MWF(data, len(data), sampFreq, winLen, winDisplacement, max_func)
print 'max: ', maxList

min_func = make_min()
minList = MWF(data, len(data), sampFreq, winLen, winDisplacement, min_func)
print 'min: ', minList

range_func = make_range()
rangeList = MWF(data, len(data), sampFreq, winLen, winDisplacement, range_func)
print 'range: ', rangeList
