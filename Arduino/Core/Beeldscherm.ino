// Besturing van het beeldscherm
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

// Draw 'RMSG Booting...' on the screen
void beeldscherm_Hello(){
  oled.setFontType(1);      // Set the text to medium/7-segment (5 columns, 3 rows worth of characters)
  oled.clear(PAGE);         // Clear the buffer.
  oled.setCursor(0,0);      // Set the text cursor to the upper-left of the screen
  oled.print("RMSG");       // Send string to buffer
  oled.setFontType(0);      // Set the text to small (10 columns, 6 rows worth of characters)
  oled.setCursor(0,17);     // Goto next line
  oled.print("Booting..."); // Send string to buffer
  oled.display();           // Output the buffer
}

