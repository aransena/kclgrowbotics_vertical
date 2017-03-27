/**
  Aran Sena - KCL
  aransena@gmail.com
  27.03.17
  MIT License
**/

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

#include "Test.h"

// declare vars
int x;
Test val1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Start Serial
}

void loop() {
  // put your main code here, to run repeatedly:
  val1.increase();
  val1.increase();
  x = val1.get_val();
  
  Serial.print("Test = ");
  Serial.println(x);
}
