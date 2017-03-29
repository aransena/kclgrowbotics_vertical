#!/usr/bin/env python
import rospy
from time import sleep
from arduino_ws.msg import Adc_Mega, HSV, LED_State
from random import randint


def rand_set():
    # return randint(0,2)
    return randint(0,255)

def cycle(H,rev):
    if rev:
        H = H-1
        if H <= 0:
            rev = False
    else:
        H = H+1
        if H >= 255:
            rev = True

    return H, rev

if __name__ == '__main__':
    led_pub = rospy.Publisher('LED_master', Adc_Mega, queue_size=10)
    rospy.init_node('interface_node', anonymous=True)

    n = rand_set
    msg = Adc_Mega()
    rev = False
    H = 0
    rev2 = True
    H2 = 255
    rev3 = False
    H3 = 0
    rev4 = False
    H4 = 128

    irev = False
    i = 0

    while True:

        H,rev = cycle(H,rev)
        H2,rev2 = cycle(H2,rev2)
        H3,rev3 = cycle(H3,rev3)
        H4,rev4 = cycle(H4,rev4)

        j = randint(0,5)
        k = randint(0,5)
        l = randint(0,6)
        m = 16 - (j+k+l)

        Ha = [H]*j
        Ha += [H2]*k
        Ha += [H3]*l
        Ha += [H4]*m

        if irev:
            i = i-1
            if i <= 0:
                irev = False
        else:
            i = i+1
            if i>=15:
                irev = True

        Ha[i] = 1
        msg.data = Ha
        led_pub.publish(msg)
        sleep(0.01)

