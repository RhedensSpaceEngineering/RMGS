// Load essential Libraries
#include <Wire.h>           // Load liberary needed for I2C
// temporary because of weird out-of-scope errors
float pitch, roll, heading;
// altitude sensor variables
float altitude,temperature; 

void setup() {
  ////////////////////
  // Communications //
  ////////////////////
  Serial.begin(9600); // start a serial communication at 9600 bits per second
  
  /////////////
  // Display //
  /////////////
  Display();
  /////////////////////
  // Rotation Sensor //
  /////////////////////
  Rotation_Sensor();
  /////////////////////
  // Altitude Sensor //
  /////////////////////
  Altitude_Sensor();
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
  
  altitudeCalc();
  temperatureCalc();
  Serial.print("altitude: "); 
  Serial.println(altitude, 2);
  Serial.print("temperature: "); 
  Serial.println(temperature, 2);
  delay(1000);

  
  /*delay(4000);
  displayDraw("Loading...", 0);
  delay(5000);
  displayBootFinished();
  delay(4000);*/
}
