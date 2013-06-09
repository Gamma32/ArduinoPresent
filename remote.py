#!/usr/bin/python
# -*- coding: utf-8 -*-

import serial
import time
import sys
import re
import uinput


events = (
        uinput.KEY_RIGHT,
        uinput.KEY_LEFT
        )
device = uinput.Device(events)


if len(sys.argv) == 3:
      ser = serial.Serial(sys.argv[1], sys.argv[2])
else:
      print "# using defaults /dev/rfcomm0 19200"
      ser = serial.Serial("/dev/rfcomm0", 19200)


while 1:
      line = ser.readline()
      sys.stdout.write(line)
       
      if "Button A" in line:
        sys.stdout.write("Next Slide!!!\n")
        device.emit(uinput.KEY_RIGHT, 1) # Press.
        device.emit(uinput.KEY_RIGHT, 0)
      elif "Button B" in line:
        sys.stdout.write("Prev Slide!!!\n")
        device.emit(uinput.KEY_LEFT, 1) # Press.
        device.emit(uinput.KEY_LEFT, 0)

