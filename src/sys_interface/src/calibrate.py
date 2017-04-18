#!/usr/bin/env python
import rospy
import time
from arduino_ws.msg import Adc_Mega

global average, count

def set_LDR_cal():
    global average
    rospy.set_param('/LDR_high', average*2.4)

def LDR_callback(data):
    global average, count

    for val in data.data:
        average = average+val

    average = average/17.0
    count = count + 1

if __name__ == '__main__':
    global average, count
    count = 0
    average = 0

    rospy.init_node('interface_node', anonymous=True)
    rospy.Subscriber("LDR_data", Adc_Mega, LDR_callback)

    while True:
        if count < 10:
            print count
            pass
        else:
            set_LDR_cal()
            break
