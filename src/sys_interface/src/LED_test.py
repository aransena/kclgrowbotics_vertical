#!/usr/bin/env python
import rospy
from time import sleep
from arduino_ws.msg import Adc_Mega, HSV, LED_State
from random import randint



if __name__ == '__main__':
    led_pub = rospy.Publisher('LED_master', Adc_Mega, queue_size=10)
    rospy.init_node('interface_node', anonymous=True)

    msg = Adc_Mega()
    i = 0
    while True:
        Ha = [-1]*16
        Ha[i] = 1
        j = i+3
        Ha[j] = 100
        msg.data = Ha
        print msg
        for k in range(0,5):
            led_pub.publish(msg)
            sleep(0.05)

        i= i+1
        if i>=12:
            i = 0
        sleep(0.1)

