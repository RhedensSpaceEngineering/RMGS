/*
 * Display
 * 
 * Connects to the Sparkfun OLED so it can be used.
 * Adds display, displayDraw, displayPrepare, displayBootStart, displayDrawStatusCode, displayBootFinished
 * 
 * Pin layout:
 * MicroOLED --------- Arduino
 *   SCL -------------- SCL (A5 on older 'Duinos')
 *   SDA -------------- SDA (A4 on older 'Duinos')
 *   VDD -------------- 3.3V
 *   GND -------------- GND
 *   RST -------------- Digital pin 9
 *   
 * Created by Arend-Jan Hengst, RMSG, 13-09-2017 
 *   
 * Hookup Guide: https://learn.sparkfun.com/tutorials/micro-oled-breakout-hookup-guide
 */
// Load OLED Library
#include <SFE_MicroOLED.h>

// Set the pins
const byte PIN_RESET = 8; // Connect RST to pin 9
const byte DC_JUMPER = 1; // Set to 1 and connect D/C to 3.3 V

// Create a MicroOLED object
MicroOLED oled(PIN_RESET, DC_JUMPER);

/*
 * Display
 * 
 * 'Constructor' of Display and creates a connection with the Arduino
 */
void Display () {
  oled.begin();     // Initialize the OLED
  oled.clear(ALL);  // Clear the display's internal memory
  oled.display();   // Display what's in the buffer (splashscreen)
  delay(1000);      // Delay 1000 ms
  oled.clear(PAGE); // Clear the buffer.
  // start boot proces
  displayBootStart();
}

/*
 * displayPrepare
 * 
 * Prepares a screen to be written to.
 * 
 * int font 0 sets the text to small (10 columns, 6 rows worth of characters)
 *          1 sets the text to medium (6 columns, 3 rows worth of characters)
 *          2 sets the text to medium/7-segment (5 columns, 3 rows worth of characters)
 *          3 sets the text to large (5 columns, 1 row worth of characters) 
 */
void displayPrepare (int font) {
  oled.setFontType(font); // set the font size
  oled.clear(PAGE);       // clean the buffer
  oled.setCursor(0,0);    // set text cursor 
}

/*
 * displayDraw
 * 
 * Draw text/int/double/float/long/boolean on screen, when max collums is reached, text continous on next row.
 * 
 * String/int/double/float/long/boolean input String that needs to be drawn
 * int font 0 sets the text to small (10 columns, 6 rows worth of characters)
 *          1 sets the text to medium (6 columns, 3 rows worth of characters)
 *          2 sets the text to medium/7-segment (5 columns, 3 rows worth of characters)
 *          3 sets the text to large (5 columns, 1 row worth of characters)
 */
template <class DisplayData> void displayDraw (DisplayData input, int font) {
  displayPrepare(font);     // Prepare the screen to be written to
  oled.print(input);        // Send text to buffer
  oled.display();           // Output the buffer to the screen
}

/* 
 * displayBootStart
 * 
 * Draw 'RMSG Booting...' on the screen
 */
void displayBootStart () {
  oled.setFontType(1);      // Set the text to medium/7-segment (5 columns, 3 rows worth of characters)
  oled.clear(PAGE);         // Clear the buffer.
  oled.setCursor(0,0);      // Set the text cursor to the upper-left of the screen
  oled.print("RMSG");       // Send string to buffer
  oled.setFontType(0);      // Set the text to small (10 columns, 6 rows worth of characters)
  oled.setCursor(0,17);     // Goto next line
  oled.print("Booting..."); // Send string to buffer
  oled.display();           // Output the buffer
  delay(sleep);
}

/*
 * displayDrawStatusCode
 * 
 * Draws a statusCode as given and sends it to the log file, and then waits for 5 seconds.
 * 
 * String statusCode The statuscode that needs to be shown.
 */
void displayDrawStatusCode (String statusCode) {
  // use displaydraw to draw the code
  displayDraw(statusCode, 1);
  // send to log file
  //sdCardPrint(statusCode);
  // wait for 5 seconds
  delay(sleep);
}

/* 
 * displayBootStart
 *  
 * Draw 'RMSG Boot Finished' on the screen 
 */
void displayBootFinished () {
  oled.setFontType(1);      // Set the text to medium/7-segment (5 columns, 3 rows worth of characters)
  oled.clear(PAGE);         // Clear the buffer.
  oled.setCursor(0,0);      // Set the text cursor to the upper-left of the screen
  oled.print("RMSG");       // Send string to buffer
  oled.setFontType(0);      // Set the text to small (10 columns, 6 rows worth of characters)
  oled.setCursor(0,17);     // Goto next line
  oled.print("Boot      Finished"); // Send string to buffer
  oled.display();           // Output the buffer
}
