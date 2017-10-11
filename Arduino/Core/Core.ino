// Load essential Libraries
#include <Wire.h>           // Load liberary needed for I2C


float pitch, roll, heading;

void setup() {
  ///////////////////
  // Commincations //
  ///////////////////
  Serial.begin(9600); // start a serial communication at 9600 bits per second
  
  /////////////////
  // Beeldscherm //
  /////////////////
  Display();
  ///////////////////
  // Rotatie Meter //
  ///////////////////
  Rotation_Sensor();
}

void loop() {
  displayBootStart();
  rotationSensorRead();
  rotationSensorCalc();
  //Serial.println("Heading: "); 
  //Serial.println(rotatie_meter_heading());

  rotationSensorCalcOrientation();
  Serial.print("Pitch, Roll: ");
  Serial.print(pitch, 2);
  Serial.print(", ");
  Serial.println(roll, 2);
  Serial.print("Heading: "); 
  Serial.println(heading, 2);
  delay(1000);
  
  /*delay(4000);
  displayDraw("Loading...", 0);
  delay(5000);
  displayBootFinished();
  delay(4000);*/
}
