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

//Create an instance of the object
MPL3115A2 altitudeSensor;

/*
 * Altitude_Sensor
 * 
 * Connects to the sensor and edits the settings
 */
void Altitude_Sensor() {

    altitudeSensor.begin(); // Get sensor online
    
    // Configure the sensor
    
    altitudeSensor.setModeAltimeter(); // Measure altitude above sea level in meters  
    
    altitudeSensor.setOversampleRate(7); // Set Oversample to the recommended 128
    altitudeSensor.enableEventFlags(); // Enable all three pressure and temp event flags 

}

/*
 * altitudeCalc
 * 
 * updates the altitude variable to the new altitude
 * 
 * readAltitude()  updates altitude
 */
void altitudeCalc(){
   altitude = altitudeSensor.readAltitude(); // read Altitude_Sensor from Breakout
}

/*
 * temperatureCalc
 * 
 * updates the temperature variable to the new temperature
 * 
 * readTemp()  updates temperature
 */
void temperatureCalc(){
  temperature = altitudeSensor.readTemp(); // read Altitude_Sensor from Breakout
}

