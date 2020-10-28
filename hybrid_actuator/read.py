# -- communication with esp32 - old white control box to read values-- #
# Author: Marisa Lim (marisa.lim@u.nus.edu)
# Evolution Innovation Lab
# National University of Singapore

# add serial communication between Arduino and Python

import serial, time
import numpy as np

class controller:
	def __init__(self):	
		self.file = open("_nrp finger 5000 cycles_.txt","a+") # create .txt file to store values
		self.controller = serial.Serial()
		# ---- changer port here ----
		self.controller.port = "COM4" # change COM port accordingly
		self.controller.baudrate = 115200
		self.controller.timeout = 1
		# ---for esp32 ----
		# self.controller.setDTR(False)
		self.controller.setRTS(False)
		# ---for esp32 ----
		self.controller.open()
		time.sleep(1) # give the connection a second to settle
		self.command = 0
		# self.start = time.time()

	def cmd(self,command): # send Python commands to Arduino serial
		self.controller.write(str(command).encode())

	def readADC(self):
		string = self.controller.readline()
		string = string.decode('utf-8')
		new_string = string.split(',')
		new_strings = new_string[0:len(new_string)]
		lengthL = len(new_strings) 
		self.decodedbytes = np.zeros(lengthL)
		# NowTime = time.time()-self.start
		# self.file.write(str(NowTime) + ',')	# get tactile values -1
		for index in range(len(new_strings)):
			toconvert = new_strings[index]
			self.decodedbytes[index] = float(toconvert)
			self.file.write(str(self.decodedbytes[index]) + ', ')	# get tactile values -1
		self.file.write('\n')
		print(self.decodedbytes)

	def StopRecording(self):
		self.file.close()

#	def cyclicActivation (self,period):
#		self.start = time.time()
#		halfway = period/2
#		while(time.time() - self.start < period):
#			while(time.time() - self.start < halfway):
#				self.file.write(str(0)+',')
#				self.readADC(0)
#			self.file.write(str(100)+',')
#			self.readADC(2)

#	def pressureControl(self,set_valve,set_pressure):
#		self.readADC()
#		# ASSUME VALVE IS OFF IN INITIAL STATE
#		if (self.decodedbytes[set_valve]<set_pressure):
#			self.controller.write(str(set_valve).encode())
#			self.read_while_rest(1)

#	def read_while_rest(self,rest_time):
#		self.start = time.time()
#		while(time.time() - self.start < (rest_time)):
#			self.readADC()

#	def toggleValve(self,set_valve):
#		self.controller.write(str(set_valve).encode())

if __name__ == '__main__':
	board = controller()
	# board.toggleValve(2)
	# board.toggleValve(3)
	# board.read_while_rest(5)
	# board.cmd(4)
	board.cmd("start") # start cyclic count on Arduino code
	while True:
		try:
			# board.cyclicActivation(1)
			board.readADC()
			# board.pressureControl(2,107)
			# board.toggleValve(2)
		except KeyboardInterrupt:
			# board.cmd(0)
			board.StopRecording()
			break

