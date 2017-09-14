// Besturing van het beeldscherm (https://learn.sparkfun.com/tutorials/micro-oled-breakout-hookup-guide)
#include <SFE_MicroOLED.h>  // Load OLED library
#include <Wire.h>           // Load liberary needed for I2C

// Set the pins
#define PIN_RESET 9 // Connect RST to pin 9
#define DC_JUMPER 1 // Set to 1 and connect D/C to 3.3 V

// Declare the MicroOLED object
MicroOLED oled(PIN_RESET, DC_JUMPER);

// Standard initialation of the OLED
void beeldscherm (){
  oled.begin();     // Initialize the OLED
  oled.clear(ALL);  // Clear the display's internal memory
  oled.display();   // Display what's in the buffer (splashscreen)
  delay(1000);      // Delay 1000 ms
  oled.clear(PAGE); // Clear the buffer.
}

/*
 * Prepares a screen to be written to
 * 
 * int font 0 sets the text to small (10 columns, 6 rows worth of characters)
 *          1 sets the text to medium (6 columns, 3 rows worth of characters)
 *          2 sets the text to medium/7-segment (5 columns, 3 rows worth of characters)
 *          3 sets the text to large (5 columns, 1 row worth of characters) 
 */
void beeldscherm_Prepare(int font){
  oled.setFontType(font); // set the font size
  oled.clear(PAGE);       // clean the buffer
  oled.setCursor(0,0);    // set text cursor 
}

/*
 * Draw text/int/double/float/long on screen, when max collums is reached, text continous on next row.
 * 
 * String/int/double/float/long input String that needs to be drawn
 * int font 0 sets the text to small (10 columns, 6 rows worth of characters)
 *          1 sets the text to medium (6 columns, 3 rows worth of characters)
 *          2 sets the text to medium/7-segment (5 columns, 3 rows worth of characters)
 *          3 sets the text to large (5 columns, 1 row worth of characters)
 */
void beeldscherm_Draw(String input, int font){
  beeldscherm_Prepare(font);// Prepare the screen to be written to
  oled.print(input);        // Send text to buffer
  oled.display();           // Output the buffer to the screen
}
void beeldscherm_Draw(int input, int font){
  beeldscherm_Prepare(font);// Prepare the screen to be written to
  oled.print(input);        // Send text to buffer
  oled.display();           // Output the buffer to the screen
}
void beeldscherm_Draw(double input, int font){
  beeldscherm_Prepare(font);// Prepare the screen to be written to
  oled.print(input);        // Send text to buffer
  oled.display();           // Output the buffer to the screen
}
void beeldscherm_Draw(float input, int font){
  beeldscherm_Prepare(font);// Prepare the screen to be written to
  oled.print(input);        // Send text to buffer
  oled.display();           // Output the buffer to the screen
}
void beeldscherm_Draw(long input, int font){
  beeldscherm_Prepare(font);// Prepare the screen to be written to
  oled.print(input);        // Send text to buffer
  oled.display();           // Output the buffer to the screen
}

/* 
 * Draw 'RMSG Booting...' on the screen 
 */
void beeldscherm_BootStart(){
  oled.setFontType(1);      // Set the text to medium/7-segment (5 columns, 3 rows worth of characters)
  oled.clear(PAGE);         // Clear the buffer.
  oled.setCursor(0,0);      // Set the text cursor to the upper-left of the screen
  oled.print("RMSG");       // Send string to buffer
  oled.setFontType(0);      // Set the text to small (10 columns, 6 rows worth of characters)
  oled.setCursor(0,17);     // Goto next line
  oled.print("Booting..."); // Send string to buffer
  oled.display();           // Output the buffer
}

/* 
 * Draw 'RMSG Boot Finished' on the screen 
 */
void beeldscherm_BootFinished(){
  oled.setFontType(1);      // Set the text to medium/7-segment (5 columns, 3 rows worth of characters)
  oled.clear(PAGE);         // Clear the buffer.
  oled.setCursor(0,0);      // Set the text cursor to the upper-left of the screen
  oled.print("RMSG");       // Send string to buffer
  oled.setFontType(0);      // Set the text to small (10 columns, 6 rows worth of characters)
  oled.setCursor(0,17);     // Goto next line
  oled.print("Boot      Finished"); // Send string to buffer
  oled.display();           // Output the buffer
}
