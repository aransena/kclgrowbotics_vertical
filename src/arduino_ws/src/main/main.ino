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
#include <arduino_ws/HSV.h>
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
  digitalWrite(13, HIGH);
  if(first_msg==true){
    pubchk = true;  
    first_msg = false;  
    
  }

  for(int i=0; i<NUM_LED; i++){
    leds[i] = CHSV(led_cmd.data[i],255,255);
  }

  FastLED.show();
  delay(10);

    
}

//% End Function defs 

//////// Setup & Loop ////////
long tstart;
void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  nh.initNode();
  nh.subscribe(led_sub); 
  nh.advertise(ldr_pub);
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





