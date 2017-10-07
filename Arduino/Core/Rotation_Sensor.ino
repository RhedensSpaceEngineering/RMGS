/*
 * Rotation_Sensor
 * 
 * Connects the Sparkfun LSM9DS1 9DOF to the arduino so it can be read out.
 * Adds Rotation_Sensor, rotationSensorUpdateValues.
 * 
 * Pin layout:
 * LSM9DS1 --------- Arduino
 *  SCL ------------- SCL (A5 on older 'Duinos')
 *  SDA ------------- SDA (A4 on older 'Duinos')
 *  VDD ------------- 3.3V
 *  GND ------------- GND
 *   
 *  Created by Arend-Jan Hengst, RMSG, 07-10-2017 
 *   
 *  Hookup Guide: https://learn.sparkfun.com/tutorials/lsm9ds1-breakout-hookup-guide
 *  Library: https://github.com/sparkfun/SparkFun_LSM9DS1_Arduino_Library/archive/master.zip
 */

// Load the LSM9DS1 library
#include <SparkFunLSM9DS1.h>

// Define the Declination (calculate from: http://www.ngdc.noaa.gov/geomag-web/#declination)
const float DECLINATION = 1.55;

// Define the variables that hold the data
float Ax, Ay, Az, Mx, My, Mz, Gx, Gy, Gz, pitch, roll, heading;
 
// SDO_XM and SDO_G are both pulled high, so our addresses are:
const int LSM9DS1_M = 0x1E; // Would be 0x1C if SDO_M is LOW
const int LSM9DS1_AG = 0x6B; // Would be 0x6A if SDO_AG is LOW

// Create a LSM9DS1 object
LSM9DS1 rotationSensor;

/*
 * Rotation_Sensor
 * 
 * 'Constructor' used to connect to the Arduino
 */
void Rotation_Sensor () {
  // Configure some settings to make communication possible
  imu.settings.device.commInterface = IMU_MODE_I2C; // Set mode to I2C
  imu.settings.device.mAddress = LSM9DS1_M;         // Set mag address to 0x1E
  imu.settings.device.agAddress = LSM9DS1_AG;       // Set ag address to 0x6B

  // initiliaze the sensor
  if (imu.begin()) {
    beeldscherm_Draw("1C0", 0); // Notify when sensor is succesfully connected
    delay(5000);
  } else {
    beeldscherm_Draw("3C0", 0); // Notify when sensor didn't connect correctly
    delay(5000);
  }
}

/*
 * Gets all data from the IMU and stores it in the memory
 * 
 * readAccel()  updates ax, ay, az
 * readMag()    updates mx, my, mz
 * readGyro()   updates gx, gy, gz
 */
void rotatie_meter_read() {
  imu.readAccel();  // update accelerometer data
  imu.readMag();    // update magnetometer data
  imu.readGyro();   // update gyroscoop data
}

/*
 * Converts all IMU data to it's corrisponding units
 * 
 * calcAccel()  updates Ax, Ay, Az
 * calcMag()    updates Mx, My, Mz
 * calcGyro()   updates Gx, Gy, Gz
 */
void rotatie_meter_calc() {
  Ax = imu.calcAccel(imu.ax); // Convert the x-axis to g's
  Ay = imu.calcAccel(imu.ay); // Convert the y-axis to g's
  Az = imu.calcAccel(imu.az); // Convert the z-axis to g's
  
  
  Mx = imu.calcMag(imu.mx); // Convert the x-axis to dps's
  My = imu.calcMag(imu.my); // Convert the y-axis to dps's
  Mz = imu.calcMag(imu.mz); // Convert the z-axis to dps's
  
  Gx = imu.calcGyro(imu.gx);  // Convert the x-axis to dps's
  Gy = imu.calcGyro(imu.gy);  // Convert the y-axis to dps's
  Gz = imu.calcGyro(imu.gz);  // Convert the z-axis to dps's
}


