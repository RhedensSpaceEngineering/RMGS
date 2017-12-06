// Load essential Libraries
#include <Wire.h>           // Load liberary needed for I2C

// temporary because of weird out-of-scope errors
float pitch, roll, heading;
float axCalculated, ayCalculated, azCalculated, mxCalculated, myCalculated, mzCalculated, gxCalculated, gyCalculated, gzCalculated;
// altitude sensor variables
float relativeAltitude, temperature;
// Used to store the data before writing to SD-card
String dataString = "";
// global sleep time
int sleep = 5000;
// keep start time
unsigned long startTime;

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
  displayDraw(millis() - startTime, 0);
  
  //delay(5000);
  //displayBootFinished();

  
  /*delay(4000);
  displayDraw("Loading...", 0);
  delay(5000);
  displayBootFinished();
  delay(4000);*/
}
