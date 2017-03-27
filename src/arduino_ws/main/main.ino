/**
  Aran Sena - KCL
  aransena@gmail.com
  27.03.17
  MIT License
**/

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Int16.h>

#define NUM_LDR 16

// declare vars

void LDR_update(int *LDR_vals){
  for(int i = 0; i < NUM_LDR; i++){
    LDR_vals[i] = analogRead(i);
  }
}

void messageCb( const std_msgs::Empty& toggle_msg){
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
}


ros::NodeHandle  nh;
ros::Subscriber<std_msgs::Empty> sub("toggle_led", messageCb );
std_msgs::String str_msg;
std_msgs::Int16 int_msg;
ros::Publisher chatter("chatter", &int_msg);

void setup()
{
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
}

int LDR_vals[NUM_LDR];
void loop()
{
  LDR_update(LDR_vals);
  for(int i = 0; i < NUM_LDR; i++){
    int_msg.data = LDR_vals[i]+(1000*i);
    //str_msg.data = ;
    chatter.publish( &int_msg );
  }
  nh.spinOnce();
  delay(1000);
}
