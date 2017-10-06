// Load essential Libraries
#include <Wire.h>           // Load liberary needed for I2C

void setup() {
  ///////////////////
  // Commincations //
  ///////////////////
  Serial.begin(9600); // start a serial communication at 9600 bits per second
  
  /////////////////
  // Beeldscherm //
  /////////////////
  beeldscherm();
  ///////////////////
  // Rotatie Meter //
  ///////////////////
  rotatie_meter();
}

void loop() {
  displayBootStart();
  rotatie_meter_read();
  rotatie_meter_calc();
  //Serial.println("Heading: "); 
  //Serial.println(rotatie_meter_heading());

  calculate();
  delay(1000);
  
  /*delay(4000);
  displayDraw("Loading...", 0);
  delay(5000);
  displayBootFinished();
  delay(4000);*/
}
