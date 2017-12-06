/*
 *  Altitude_Sensor
 * 
 * Connects the Sparkfun MPL3115A2 to the arduino so it can be read out.
 * Adds Altitude_Sensor, altitudeCalc, temperatureCalc
 * 
 * Pin layout:
 * MPL3115A2 --------- Arduino
 *  SCL ------------- SCL (A5 on older 'Duinos')
 *  SDA ------------- SDA (A4 on older 'Duinos')
 *  VDD ------------- 3.3V
 *  GND ------------- GND
 *  
 * Created by Tim Hiemstra & Arend-Jan Hengst, RMSG, 12-11-2017
 * 
 * Hookup Guide: https://learn.sparkfun.com/tutorials/mpl3115a2-pressure-sensor-hookup-guide
 * Library: https://github.com/sparkfun/SparkFun_MPL3115A2_Breakout_Arduino_Library/archive/master.zip
 */
#include "SparkFunMPL3115A2.h" // Load MPL3115A2 library

// Create an instance of the object
MPL3115A2 altitudeSensor;

// Used to keep the start altitude
float startAltitude;

/*
 * Altitude_Sensor
 * 
 * Connects to the sensor and edits the settings
 */
void Altitude_Sensor() {
  // get sensor online
  altitudeSensor.begin();
  
  // check if online
  Wire.beginTransmission(MPL3115A2_ADDRESS); // Initialize the Tx buffer
  Wire.write(OUT_P_MSB);  // Address of data to get
  Wire.endTransmission(false); // Send the Tx buffer, but send a restart to keep connection alive
  Wire.requestFrom(MPL3115A2_ADDRESS, 1); // Read one byte form the slave register address
  if (Wire.read() == 255) { // check if response is not empty (M0 PRO == 0, UNO == 255)
    displayDrawStatusCode("1B0"); // Notify when sensor is succesfully connected
  } else {
    displayDrawStatusCode("3B0"); // Notify when sensor didn't connect correctly
  }
  
  // Configure the sensor
  altitudeSensor.setModeAltimeter(); // Measure altitude above sea level in meters  
  altitudeSensor.setOversampleRate(7); // Set Oversample to the recommended 128
  altitudeSensor.enableEventFlags(); // Enable all three pressure and temp event flags

  // Set start altitude
  startAltitude = altitudeSensor.readAltitude();

}

/*
 * altitudeCalc
 * 
 * updates the altitude variable to the new altitude
 * and converts it to the altitude relative to starting point
 */
void altitudeCalc(){
  // Starting altitude - Current altitude = relative altitude
  relativeAltitude = startAltitude - altitudeSensor.readAltitude();
}

/*
 * temperatureCalc
 * 
 * updates the temperature variable to the new temperature
 */
void temperatureCalc(){
  temperature = altitudeSensor.readTemp(); // read Altitude_Sensor from Breakout
}

