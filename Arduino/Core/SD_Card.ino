/*
 *  SD_Card
 * 
 * Connects the MicroSD to the arduino so it can be read out.
 * Adds SD_Card, sdCardOpenFile, sdCardPrint, sdCardCloseFile\
 * 
 * Pin layout:
 * MicroSD --------- Arduino
 *  VCC ------------- 5V 
 *   CS ------------- D10 
 *   DI ------------- D11
 *  SCK ------------- D13
 *   D0 ------------- D12
 *  GND ------------- GND
 * 
 * Created by Tim Hiemstra & Arend-Jan Hengst, RMSG, 12-11-2017 
 * 
 * Hookup Guide: https://learn.sparkfun.com/tutorials/microsd-breakout-with-level-shifter-hookup-guide, https://learn.adafruit.com/adafruit-micro-sd-breakout-board-card-tutorial/wiring
 * Library: Inbuild Arduino SD library: https://www.arduino.cc/en/Reference/SD
 */

#include <SPI.h> // Load SPI library
#include <SD.h> // Load SD library

// Define constant variables
const byte CHIP_SELECT = 10;
const String FILE_NAME = "log.txt";

File dataFile;

/*
 * SD_Card
 * 
 * Tries to initialise a connection with the SD-card,
 * when SD-card cannot be initialised,
 * the program goes in an infinite loop and tells to RESET. 
 * 
 */
void SD_Card() {
  Serial.println("SD Card Called");
  // check if SD-card can be initialised
  while (!SD.begin(CHIP_SELECT)) {
    delay(1000); // wait
    Serial.println("SD Card initialization failed!");
    displayDraw("3D0", 1); // notify that the SD-Card hasn't been initialised
    delay(sleep); // wait
  }
  delay(1000); // wait
  //Serial.println("SD Card Display");
  displayDraw("1D0", 1); // notify that the SD-Card has been initialised
  //Serial.println("SD Card Initialised");
  delay(sleep); // wait
}

/*
 * sdCaredOpenFile
 * 
 * opens the standard file, as declared in FILE_NAME
 * Tries 1 more time when failed to open file.
 */
boolean sdCardOpenFile() {
  dataFile = SD.open(FILE_NAME, FILE_WRITE); // opening file
  // check if file is opened
  if (!dataFile) {
    // notify
    displayDraw("2D1", 0);
    // wait
    delay(1000);
    // try again once
    dataFile = SD.open(FILE_NAME, FILE_WRITE); // opening file
    // Check if file opened
    if (!dataFile) {
      // file didn't open, so return false
      return false;
    }
  }
  // file openend, so return true
  return true;
}

/*
 * sdCardPrint
 * 
 * Put a text/int/double/float/long/boolean in file
 * 
 * String/int/double/float/long/boolean input String that needs to be saved
 */
template <class sdCardData> void sdCardPrint(sdCardData input) {
  dataFile.println(input);
}

/*
 * sdCardCloseFile
 * 
 * closes file opened by sdCardOpenFile()
 */
void sdCardCloseFile() {
  dataFile.close();
}
