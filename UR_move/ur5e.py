# *************************** AUTHOR: KHIN PHONE MAY *****************************
# ******************* EI LAB, ADVANCED ROBOTICS CENTRE, NUS **********************
# ************************** biekpm@nus.edu.sg ***********************************
# DESCRIPTION : move UR by entering the coordinates in pos and control the finger 
# flexion via an external pneumatic control box. Please check the Com Port of 
# the control box before starting the program. 
# ********************************************************************************

import os, sys, glob
sys.path.append('../UR_move/general') #general libraries
import numpy as np
from time import sleep

from UR10 import *
from valve import *

class PickNPlace():
	def __init__(self):

		self.pump = pumpvalve()
		time.sleep(1)

		ip =  '192.168.1.253' 
		port = 30001 
		self.UR10Cont = UR10Controller(ip,port_send=port)
		self.UR10Cont.connect() 

		print("Starting")	

	def start(self):

		#change UR coordinates in pos
		#coordinates need to be taken from BASE Feature in UR Tablet

		poshome = [-26.90, 460.70, 229.15, 0.035, 3.156, -0.017]

		posbroccoli_up1 = [203.63, 574.55, 229.15, 0.035, 3.156, -0.017]
		posbroccoli_pick = [203.63, 574.55, 109.50, 0.035, 3.156, -0.017]
		posbroccoli_up2 = [-107.29, 456.97, 229.15, 2.089, -2.341, 0.028]
		posbroccoli_drop = [-107.29, 456.97, 124.13, 2.089, -2.341, 0.028]

		possau_up1 = [137.95, 579.10, 229.15, 0.035, 3.156, -0.017]
		possau_pick = [137.95, 579.10, 107.80, 0.035, 3.156, -0.017]
		possau_up2 = [-147.70, 464.55, 229.15, 2.272, 2.196, 0.004]
		possau_drop = [-147.70, 464.55, 134.99, 2.272, 2.196, 0.004] #142.99

		poscake_up1 = [249.75, 394.13, 229.15, 0.035, -3.127, 0.017]
		poscake_pick = [249.75, 394.13, 111.15, 0.035, -3.127, 0.017]
		poscake_up2 = [-176.32, 468.24, 229.15, 2.161, -2.276, 0.028]
		poscake_drop = [-176.32, 468.24, 122.99, 2.161, -2.276, 0.028]

		poscherry1_up1 = [131.05, 413.56, 229.15, 0.035, 3.156, 0.017]
		poscherry1_pick = [131.05, 413.56, 112.74, 0.035, 3.156, 0.017]
		poscherry1_up2 = [-216.30, 467.70, 229.15, 0.035, 3.156, 0.017]
		poscherry1_drop = [-216.30, 467.70, 124.35, 0.035, 3.156, 0.017]

		poscherry2_up1 = [134.75, 354.98, 229.15, 0.035, 3.156, 0.017] #353.98
		poscherry2_pick = [134.75, 354.98, 109.59, 0.035, 3.156, 0.017] #353.98
		poscherry2_up2 = [-220.81, 445.54, 229.15, 0.035, 3.156, 0.017]
		poscherry2_drop = [-220.81, 445.54, 135.62, 0.035, 3.156, 0.017]

		# broccoli
		self.UR10Cont.movej(poshome,1)
		sleep(1)
		self.UR10Cont.movej(posbroccoli_up1,1)
		sleep(1)
		self.UR10Cont.movej(posbroccoli_pick,1)
		sleep(1)
		self.pump.toggle(sa1)
		sleep(1)
		self.UR10Cont.movej(posbroccoli_up1,1)
		sleep(1) 
		self.UR10Cont.movej(posbroccoli_up2,1)
		sleep(1)
		self.UR10Cont.movej(posbroccoli_drop,1)
		sleep(1)
		self.pump.toggle(sa0)
		sleep(0.5)
		self.UR10Cont.movej(posbroccoli_up2,1)
		sleep(1)

		# sausage
		self.UR10Cont.movej(possau_up1,1)
		sleep(1)
		self.UR10Cont.movej(possau_pick,1)
		sleep(1)
		self.pump.toggle(sa1)
		sleep(2.5)
		self.UR10Cont.movej(possau_up1,1)
		sleep(1) 
		self.UR10Cont.movej(possau_up2,1)
		sleep(1)
		self.UR10Cont.movej(possau_drop,1)
		sleep(1)
		self.pump.toggle(sa0)
		sleep(0.5)
		self.UR10Cont.movej(possau_up2,1)
		sleep(1)

		# cake
		self.UR10Cont.movej(poscake_up1,1)
		sleep(1)
		self.UR10Cont.movej(poscake_pick,1)
		sleep(1)
		self.pump.toggle(sa1)
		sleep(1)
		self.UR10Cont.movej(poscake_up1,1)
		sleep(1) 
		self.UR10Cont.movej(poscake_up2,1)
		sleep(1)
		self.UR10Cont.movej(poscake_drop,1)
		sleep(1)
		self.pump.toggle(sa0)
		sleep(0.5)
		self.UR10Cont.movej(poscake_up2,1)
		sleep(1)

		# cherry 1
		self.UR10Cont.movej(poscherry1_up1,1)
		sleep(1)
		self.UR10Cont.movej(poscherry1_pick,1)
		sleep(1)
		self.pump.toggle(sa1)
		sleep(2)
		self.UR10Cont.movej(poscherry1_up1,1)
		sleep(1) 
		self.UR10Cont.movej(poscherry1_up2,1)
		sleep(1)
		self.UR10Cont.movej(poscherry1_drop,1)
		sleep(1)
		self.pump.toggle(sa0)
		sleep(0.5)
		self.UR10Cont.movej(poscherry1_up2,1)
		sleep(1)
		
		# cherry 2
		self.UR10Cont.movej(poscherry2_up1,1)
		sleep(1)
		self.UR10Cont.movej(poscherry2_pick,1)
		sleep(1)
		self.pump.toggle(sa1)
		sleep(2)
		self.UR10Cont.movej(poscherry2_up1,1)
		sleep(1) 
		self.UR10Cont.movej(poscherry2_up2,1)
		sleep(1)
		self.UR10Cont.movej(poscherry2_drop,1)
		sleep(1)
		self.pump.toggle(sa0)
		sleep(0.5)
		self.UR10Cont.movej(poscherry2_up2,1)
		sleep(2)
		self.UR10Cont.movej(poshome,1)
		sleep(2)


		# to inflate, toggle either 3,4,5 or 6
		# to turn off all valves, toggle 2

		# self.pump.toggle(5)
		# sleep(2)
		# self.pump.toggle(2)
		# sleep(3) 

if __name__ == '__main__':

	demo = PickNPlace()
	demo.start()