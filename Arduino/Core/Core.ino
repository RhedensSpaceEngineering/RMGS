/*
 * Core
 * 
 * Contains most of global variables so they can be used in the entire program
 * Also Contains the setup function which calls the setup functions of all sensors.
 * In the loop function all data is gathered and send to the SD card.
 *  
 * Created by Tim Hiemstra & Arend-Jan Hengst, RMSG, 17-01-2018
 * 
 * Repository: https://github.com/RhedensSpaceEngineering/RMGS
 */

// Load essential Libraries
#include <Wire.h>           // Load liberary needed for I2C

// temporary because of weird out-of-scope errors
float pitch, roll, heading;
float axCalculated, ayCalculated, azCalculated, mxCalculated, myCalculated, mzCalculated, gxCalculated, gyCalculated, gzCalculated;
// altitude sensor variables
// relativeAltitude is always equals to 0 at the start of the program
float relativeAltitude = 0, temperature;
// Used to store the data before writing to SD-card
String dataString = "";
// global sleep time
int sleep = 5000;
// keep start time
unsigned long startTime;

/*
 * setup
 * 
 * Sets the entire program up by starting communications and the sensors and the SD card.
 */
void setup() {
  ////////////////////
  // Communications //
  ////////////////////
  Serial.begin(9600); // start a serial communication at 9600 bits per second
  /////////////////////
  //     Display     //
  /////////////////////
  Display();
  /////////////////////
  //     SD Card     //
  /////////////////////
  //Serial.println("SD Card Call");
  SD_Card();
  /////////////////////
  // Rotation Sensor //
  /////////////////////
  Rotation_Sensor();
  /////////////////////
  // Altitude Sensor //
  /////////////////////
  Altitude_Sensor();

  // Create a header in the log file
  if (sdCardOpenFile()) {
    // save data
    sdCardPrint("Time,Pitch,Roll,Heading,Altitude,Temperature,ax,ay,az,mx,my,mz,gx,gy,gz");
    // close the file
    sdCardCloseFile();
  }
  
  // notify
  displayBootFinished();
}

/*
 * loop
 * 
 * The core of the program which every lap collects all data and sends it to the SD card.
 */
void loop() {
  // set start time
  startTime = millis();
  // put time in data string
  dataString += String(startTime) + ",";
  
  // output rotation data
  rotationSensorRead();
  rotationSensorCalc();
  rotationSensorCalcOrientation();
  Serial.print("Pitch, Roll: ");
  Serial.print(pitch, 2);
  Serial.print(", ");
  Serial.println(roll, 2);
  Serial.print("Heading: "); 
  Serial.println(heading, 2);
  // put in data string
  dataString += String(pitch) + ",";
  dataString += String(roll) + ",";
  dataString += String(heading) + ",";

  // output temperature and altitude data
  altitudeCalc();
  temperatureCalc();
  Serial.print("relative altitude: "); 
  Serial.println(relativeAltitude, 2);
  Serial.print("temperature: "); 
  Serial.println(temperature, 2);
  // put in data string
  dataString += String(relativeAltitude) + ",";
  dataString += String(temperature) + ",";
  
  // put all raw data in data string
  dataString += String(axCalculated) + ",";
  dataString += String(ayCalculated) + ",";
  dataString += String(azCalculated) + ",";
  dataString += String(mxCalculated) + ",";
  dataString += String(myCalculated) + ",";
  dataString += String(mzCalculated) + ",";
  dataString += String(gxCalculated) + ",";
  dataString += String(gyCalculated) + ",";
  dataString += String(gzCalculated);

  // save to SD card, when file is available
  if (sdCardOpenFile()) {
    // save data
    sdCardPrint(dataString);
    // close the file
    sdCardCloseFile();
  }
  // clear data string buffer
  dataString = "";

  // display end time
  Serial.println("End time: " + String(millis() - startTime));
  displayDraw(roll, 0);
  //displayDraw(millis() - startTime, 0);
}
