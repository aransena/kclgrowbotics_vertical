/**
  Aran Sena - KCL
  aransena@gmail.com
  27.03.17
  MIT License
**/
#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif
#include <ros.h>
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
void LDR_update(int *LDR_vals);

// declare vars
int LDR_vals[NUM_LDR];
int LED_vals[NUM_LEDS];

ros::NodeHandle  nh;

arduino_ws::Adc_Mega ldr_msg;
ros::Publisher ldr_pub("LDR_data", &ldr_msg);

CRGB leds[NUM_LEDS];

void LDR_update(arduino_ws::Adc_Mega &ldr_msg){//int *LDR_vals) {
  for(int i=0; i<NUM_LDR; i++){
    ldr_msg.data[i] = analogRead(i);
  }
  
}

long tstart;
void setup()
{
  nh.initNode();
  nh.advertise(ldr_pub);


  //delay(5000);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  
}

void loop()
{
  LDR_update(ldr_msg);//LDR_vals);
  
  for(int i = 0; i < NUM_LDR; i++){
    if(ldr_msg.data[i]<300){//LDR_vals[i]
      leds[i]=CRGB::Green;
    }
    else if(ldr_msg.data[i]<400){
      leds[i]=CRGB::Blue;
    }
    else if(ldr_msg.data[i]>400){
      leds[i]=CRGB::Red;
    }
  }
  
  
//  delay(10);
  
  ldr_pub.publish( &ldr_msg );
//  
  nh.spinOnce();
  delay(20);
  FastLED.show();
  //delay(20);
}






