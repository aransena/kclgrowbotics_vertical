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

//////// defs ////////
#define NUM_LDR 16
#define NUM_LED 16
#define DATA_PIN 3
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100

//% End defs

//////// Function Prototypes ////////
void LDR_update(int *LDR_vals);
void LED_callback(const arduino_ws::Adc_Mega& led_cmd);

//% End Function Prototypes 

//////// Variable defs ////////
int LDR_vals[NUM_LDR];
int LED_vals[NUM_LED];
CRGB leds[NUM_LED];
bool first_msg = true;
bool pubchk = false;

//% End Variable defs 

//////// ROS defs ////////
ros::NodeHandle  nh;
arduino_ws::Adc_Mega ldr_msg;
ros::Publisher ldr_pub("LDR_data", &ldr_msg);
ros::Subscriber<arduino_ws::Adc_Mega> led_sub("LED_interface", LED_callback );


//% End ROS defs 

//////// Function defs ////////
void LDR_update(arduino_ws::Adc_Mega &ldr_msg){//int *LDR_vals) {
  for(int i=0; i<NUM_LDR; i++){
    ldr_msg.data[i] = analogRead(i);
  }
  
}

void LED_callback(const arduino_ws::Adc_Mega& led_cmd){
  
  if(first_msg==true){
    pubchk = true;  
    first_msg = false;  
  }
    for(int i=0; i<NUM_LDR; i++){
      
      switch (led_cmd.data[i]) {
        case 0:    // your hand is on the sensor
          //leds[i]=CRGB::Blue;
          leds[i]=CHSV( 160, 255, 255);
          break;
        case 1:    // your hand is close to the sensor
          //leds[i]=CRGB::Green;
          leds[i]=CHSV( 100, 255, 255);
          break;
        case 2:    // your hand is a few inches from the sensor
          //leds[i]=CRGB::Red;
          leds[i]=CHSV( 224, 255, 255);
      }
    }
    digitalWrite(13, HIGH-digitalRead(13));   // blink the led

    FastLED.show();
}

//% End Function defs 

//////// Setup & Loop ////////
long tstart;
void setup()
{
  pinMode(13, OUTPUT);

  nh.initNode();
  nh.subscribe(led_sub); 
//  nh.advertise(ldr_pub);
  nh.spinOnce();
  
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LED);  
  tstart = millis();
}

void loop()
{
  LDR_update(ldr_msg);//LDR_vals);  
  //if(millis() - tstart>30000){
  if(pubchk == true){
    ldr_pub.publish( &ldr_msg );  
    delay(20);
  }
  else{
    delay(20);
  }
  
  nh.spinOnce();
  
  
  
}

//% End Program 




