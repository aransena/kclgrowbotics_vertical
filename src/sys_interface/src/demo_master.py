#!/usr/bin/env python
import rospy
from arduino_ws.msg import Adc_Mega


if __name__ == '__main__':
    led_pub = rospy.Publisher('LED_master', Adc_Mega, queue_size=10)
    rospy.init_node('interface_node', anonymous=True)

    while True:
        msg = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
        led_pub.publish(msg)
