/*
 * Rotation_Sensor
 * 
 * Connects the Sparkfun LSM9DS1 9DOF to the arduino so it can be read out.
 * Adds Rotation_Sensor, rotationSensorRead, rotationSensorCalc, rotationSensorCalcOrientation.
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
/*place holder*/
 
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
  rotationSensor.settings.device.commInterface = IMU_MODE_I2C; // Set mode to I2C
  rotationSensor.settings.device.mAddress = LSM9DS1_M;         // Set mag address to 0x1E
  rotationSensor.settings.device.agAddress = LSM9DS1_AG;       // Set ag address to 0x6B

  // initiliaze the sensor
  if (rotationSensor.begin()) {
    displayDrawStatusCode("1C0"); // Notify when sensor is succesfully connected
  } else {
    displayDrawStatusCode("3C0"); // Notify when sensor didn't connect correctly
  }
}

/*
 * rotationSensorRead
 * 
 * Gets all data from the IMU and stores it in the memory
 * 
 * readAccel()  updates ax, ay, az
 * readMag()    updates mx, my, mz
 * readGyro()   updates gx, gy, gz
 */
void rotationSensorRead() {
  // check if new accelorometer data is available
  if (rotationSensor.accelAvailable()) {
    // update accelerometer data
    rotationSensor.readAccel();  
  } else {
    // Display a warning code if no data is available
    displayDrawStatusCode("2C1A");
  }
  // check if new magnetometer data is available
  if (rotationSensor.magAvailable()) {
    // update magnetometer data
    rotationSensor.readMag();  
  } else {
    // Display a warning code if no data is available
    displayDrawStatusCode("2C1B");
  }
  // check if new gyroscope data is available
  if (rotationSensor.gyroAvailable()) {
    // update Gyroscope data
    rotationSensor.readGyro();  
  } else {
    // Display a warning code if no data is available
    displayDrawStatusCode("2C1C");
  }
}

/*
 * rotationSensorCalc
 * 
 * Converts all IMU data to it's corrisponding units
 * 
 * calcAccel()  updates Ax, Ay, Az
 * calcMag()    updates Mx, My, Mz
 * calcGyro()   updates Gx, Gy, Gz
 */
void rotationSensorCalc() {
  // convert the accelerometer data
  axCalculated = rotationSensor.calcAccel(rotationSensor.ax); // Convert the x-axis to g's
  ayCalculated = rotationSensor.calcAccel(rotationSensor.ay); // Convert the y-axis to g's
  azCalculated = rotationSensor.calcAccel(rotationSensor.az); // Convert the z-axis to g's
  
  // convert the magnetometer data  
  mxCalculated = rotationSensor.calcMag(rotationSensor.mx); // Convert the x-axis to dps's
  myCalculated = rotationSensor.calcMag(rotationSensor.my); // Convert the y-axis to dps's
  mzCalculated = rotationSensor.calcMag(rotationSensor.mz); // Convert the z-axis to dps's
  
  // convert the gyroscope data
  gxCalculated = rotationSensor.calcGyro(rotationSensor.gx);  // Convert the x-axis to dps's
  gyCalculated = rotationSensor.calcGyro(rotationSensor.gy);  // Convert the y-axis to dps's
  gzCalculated = rotationSensor.calcGyro(rotationSensor.gz);  // Convert the z-axis to dps's
}

/*
 * rotationSensorCalcOrientation
 * 
 * Calculates the Heading, Pitch and roll and stores them.
 * heading contains the angle in degrees.
 * pitch the slope in degrees.
 * roll the rotation in degrees.
 */

void rotationSensorCalcOrientation() {
  // create temporary variables for calculation purposes
  // Because the magnetomer's x and y axes are opposite to the accelerometer,
  // the my and mx are substituded for each other.
  float aX = rotationSensor.ax;
  float aY = rotationSensor.ay;
  float aZ = rotationSensor.az;
  float mX = -rotationSensor.my;
  float mY = -rotationSensor.mx;
  float mZ = rotationSensor.mz;
  
  // calculate the roll
  roll = atan2(aY, aZ);
  
  // calculate the pitch
  pitch = atan2(-aX, sqrt(aY * aY + aZ * aZ));
  
  // calculate the heading
  // make sure it is in the atan range, according to these rules:
  // heading (y>0) = 90 - [arcTAN(x/y)]*180/π
  // heading (y<0) = 270 - [arcTAN(x/y)]*180/π
  // heading (y=0, x<0) = 180.0 (or π)
  // heading (y=0, x>0) = 0.0
  if (mY == 0) {
    if (mX < 0) {
      heading = PI;
    } else {
      heading = 0;
    }
  } else {
    heading = atan2(mX, mY);
  }

  // substract the declination and convert it to radians
  heading -= 1.55 * PI/180;

  // make sure the heading follows the first 2 rules from above
  if (heading > PI) {
    heading -= (2 * PI);
  } else if (heading < -PI) {
    heading += (2 * PI);
  } else if (heading < 0) {
    heading += 2 * PI;
  }

  // convert everything from degrees to radians
  heading *= 180.0 / PI;
  pitch *= 180.0 / PI;
  roll  *= 180.0 / PI;
}




