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
#define NUM_LEDS 60
#define DATA_PIN 3
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100

// prototypes
void LEDControl( const arduino_ws::Adc_Mega& LEDctl_msg);
void LDR_update(int *LDR_vals);

// declare vars
int LDR_vals[NUM_LDR];
int LED_vals[NUM_LEDS];

arduino_ws::LED_State led_msg;
arduino_ws::Adc_Mega ldr_msg;

ros::NodeHandle  nh;
ros::Subscriber<arduino_ws::Adc_Mega> led_ctl("LDR_data", LEDControl );
ros::Publisher led_pub("LED_data", &led_msg);
ros::Publisher ldr_pub("LDR_data", &ldr_msg);

CRGB leds[NUM_LEDS];


void LDR_update(int *LDR_vals) {
  for (int i = 0; i < NUM_LDR; i++) {
    LDR_vals[i] = analogRead(i);
  }
}



void LEDControl( const arduino_ws::Adc_Mega& LEDctl_msg) {
  if (LEDctl_msg.data[0] > 200) {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }

}


void setup()
{
  //delay(3000); //safety delay
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);

  pinMode(13, OUTPUT);
  nh.initNode();
  nh.advertise(ldr_pub);
  //nh.advertise(led_pub);
  nh.subscribe(led_ctl);

//  led_msg.red = malloc(NUM_LEDS);
//  led_msg.green = malloc(NUM_LEDS);
//  led_msg.blue = malloc(NUM_LEDS);
//  
//  led_msg.red_length = NUM_LEDS;
//  led_msg.red = malloc(NUM_LEDS);
//
//  led_msg.green_length = NUM_LEDS;
//  
//  led_msg.blue_length = NUM_LEDS;

}



void loop()
{
  LDR_update(LDR_vals);
  
  led_msg.id = 0;
  led_msg.red = 1;
  led_msg.green = 2;
  led_msg.blue = 3;
  for(int i = 0; i < NUM_LDR; i++){
    if(LDR_vals[i]<300){
      leds[i]=CRGB::Green;
    }
    else if(LDR_vals[i]<400){
      leds[i]=CRGB::Blue;
    }
    else if(LDR_vals[i]>400){
      leds[i]=CRGB::Red;
    }
  }

  memcpy(&ldr_msg.data, &LDR_vals, sizeof ldr_msg.data);

  ldr_pub.publish( &ldr_msg );
  //led_pub.publish(&led_msg);


//  led_pub.publish(&led_msg);
  nh.spinOnce();
  FastLED.show();
  delay(10);
}






