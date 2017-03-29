#!/usr/bin/env python
import rospy
from time import sleep
from arduino_ws.msg import Adc_Mega
from random import randint


def rand_set():
    return randint(0,2)

if __name__ == '__main__':
    led_pub = rospy.Publisher('LED_master', Adc_Mega, queue_size=10)
    rospy.init_node('interface_node', anonymous=True)

    n = rand_set
    msg = Adc_Mega()
    while True:

        msg.data = []
        for i in range(0,16):
            msg.data.append(n())
        print msg

        led_pub.publish(msg)
        sleep(0.5)
