// Aran Sena
// KCL
// MIT License
// aransena@gmail.com
// 27.03.17


// declare vars
int LDRpin = A0;
int LDRvalue = 0;

void setup() {
  Serial.begin(9600); // Start Serial
}

void loop() {
  // read LDR
  LDRvalue = analogRead(LDRpin);

  // send out LDR
  Serial.print("LDR = ");
  Serial.println(LDRvalue);
  delay(10);
  
}
