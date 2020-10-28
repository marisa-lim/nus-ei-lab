# *************************** AUTHOR: MARISA LIM *********************************
# ******************* EI LAB, ADVANCED ROBOTICS CENTRE, NUS **********************
# ************************** marisa.lim@u.nus.edu ********************************
# DESCRIPTION :control the finger flexion via an external pneumatic control box. 
# ********************************************************************************

import serial, time
import numpy as np

class pumpvalve:
	def __init__(self):	
		self.controller = serial.Serial()
		# ---- changer port here ----
		self.controller.port = "COM3"
		self.controller.baudrate = 115200
		self.controller.timeout = 1
		self.controller.setRTS(False)
		self.controller.open()
		time.sleep(1)

	def toggle(self,set_valve):
		self.controller.write(str(set_valve).encode())

if __name__ == '__main__':
	board = pumpvalve()		
	board.toggle("mtp") 

		