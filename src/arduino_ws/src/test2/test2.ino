/* 
 * rosserial Ultrasound Example
 * 
 * This example is for the Maxbotix Ultrasound rangers.
 */

#include <ros.h>
#include <ros/time.h>

#include <arduino_ws/LED_State.h>

ros::NodeHandle  nh;


arduino_ws::LED_State led_msg;
ros::Publisher pub_led( "/LED_Pub", &led_msg);

long range_time;

void setup()
{
  range_time = 0;
  nh.initNode();
  nh.advertise(pub_led);
}

void loop()
{
  
  if ( millis() >= range_time ){
    for(int i = 0; i < 16; i++){
      led_msg.red[i] = 1;//Global_LED_data.data[i];
      led_msg.green[i] = 2;//Global_LED_data.data[i]*10;
      led_msg.blue[i] = 3;//Global_LED_data.data[i]*100;
    }

    pub_led.publish(&led_msg);
    range_time =  millis() + 50;
  }
  
  nh.spinOnce();
}
