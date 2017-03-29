#!/usr/bin/env python
import rospy
import time
from arduino_ws.msg import Adc_Mega

global dt, first, upper_lim, led_pub

def get_LDR_cal():
    global upper_lim
    try:
        upper_lim = rospy.get_param('/LDR_high')
    except:
        upper_lim = 200
        rospy.set_param('/LDR_high',upper_lim)

def LDR_callback(data):
    global dt, first, upper_lim

    if first:
        get_LDR_cal()
        first = False

    if time.time()-dt > 1:
        get_LDR_cal()
        dt = time.time()

    shelf_state_pub = rospy.Publisher('shelf_state', Adc_Mega, queue_size=10)

    output = Adc_Mega()

    output.data = []
    for val in data.data:
        if val > upper_lim:
            output.data.append(0)
        else:
            output.data.append(1)
    shelf_state_pub.publish(output)


def LED_callback(data):
    global led_pub
    #  print data.data
    led_pub.publish(data)


if __name__ == '__main__':
    global dt, first, led_pub
    first = True
    dt = time.time()
    rospy.init_node('interface_node', anonymous=True)
    rospy.Subscriber("LDR_data", Adc_Mega, LDR_callback)
    rospy.Subscriber("LED_master", Adc_Mega, LED_callback)
    led_pub = rospy.Publisher('LED_interface', Adc_Mega, queue_size=10)

    rospy.spin()
