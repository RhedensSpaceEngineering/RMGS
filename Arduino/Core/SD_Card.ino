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
 *   CD ------------- D9
 *  GND ------------- GND
 * 
 * Created by Tim Hiemstra & Arend-Jan Hengst, RMSG, 12-11-2017 
 * 
 * Hookup Guide: https://learn.sparkfun.com/tutorials/microsd-breakout-with-level-shifter-hookup-guide
 * Library: Inbuild Arduino SD library: https://www.arduino.cc/en/Reference/SD
 */

#include <SPI.h> // Load SPI library
#include <SD.h> // Load SD library

const byte CHIP_SELECT = 10;
const String FILE_NAME = "log.txt";

File dataFile;

/*
 * SD_Card
 * 
 * Connects to the sensor and edits the settings
 * 
 */
void SD_Card() {
  // check if SD Card can be initialised
  if (!SD.begin(CHIP_SELECT)) {
    displayDraw("3D0", 0); // notify that the SD Card hasn't been initialised
  } else {
    displayDraw("1D0", 0); // notify that the SD Card has been initialised
  }
}

/*
 * sdCardOpenFile
 * 
 * opens file with path fileName
 * 
 * File fileName the file that needs to be opened
 */
void sdCardOpenFile(String fileName) {
  dataFile = SD.open(fileName, FILE_WRITE); // opening file
  // check if file is opened
  if (!dataFile) {
    displayDraw("2D1", 0); 
  }
}

/*
 * sdCaredOpenFile
 * 
 * opens the standard file, as declared in FILE_NAME
 */
void sdCardOpenFile() {
  dataFile = SD.open(FILE_NAME, FILE_WRITE); // opening file
  // check if file is opened
  if (!dataFile) {
    displayDraw("2D1", 0); 
  }
}

/*
 * sdCardPrint
 * 
 * Put a text/int/double/float/long/boolean in file
 * 
 * String/int/double/float/long/boolean input String that needs to be saved
 */
void sdCardPrint(String input) {
  dataFile.println(input);
}
void sdCardPrint(int input) {
  dataFile.println(input);
}
void sdCardPrint(double input) {
  dataFile.println(input);
}
void sdCardPrint(float input) {
  dataFile.println(input);
}
void sdCardPrint(long input) {
  dataFile.println(input);
}
void sdCardPrint(char input) {
  dataFile.println(input);
}
void sdCardPrint(boolean input) {
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










