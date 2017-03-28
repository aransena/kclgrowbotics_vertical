/**
  Aran Sena - KCL
  aransena@gmail.com
  27.03.17
  MIT License
**/

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <arduino_ws/Adc_Mega.h>
#include <arduino_ws/LED_State.h>
#include "FastLED.h"

#define NUM_LDR 16
#define NUM_LEDS 16
#define DATA_PIN 3
#define LED_TYPE WS2811
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100


// declare vars
int RED[NUM_LEDS];
int GREEN[NUM_LEDS];
int BLUE[NUM_LEDS];
int timer = 0;

arduino_ws::LED_State led_msg;
arduino_ws::Adc_Mega ldr_msg;
arduino_ws::Adc_Mega Global_LED_data;

ros::NodeHandle  nh;
ros::Publisher led_pub("LED_data", &led_msg);


void setup()
{
  //delay(3000);
  //FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.advertise(led_pub);

}

int LDR_vals[NUM_LDR];
void loop()
{

if (millis() > timer){
    for(int i = 0; i < NUM_LEDS; i++){
      led_msg.red[i] = 1;//Global_LED_data.data[i];
      led_msg.green[i] = 2;//Global_LED_data.data[i]*10;
      led_msg.blue[i] = 3;//Global_LED_data.data[i]*100;
    }
  
    led_pub.publish( &led_msg );
    timer = millis()+50;
}
  
  nh.spinOnce();
  //delay(10);
}






