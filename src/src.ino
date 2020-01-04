#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#include "protocol.h"

/// program version
#define VERSION "arduino-ws28xxled 0.1\n"
/// program version
#define AUTHOR "spasz\n"
///
#define LED_DELAY 25 // Time (in milliseconds) to pause between pixels
/// control pin
#define PIN        A5
/// Number of leds
#define NUMPIXELS 50
/// Create driver
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Communication section
// ------------------------------------

// Create protocol object
static Protocol protocol;

void CommunicationInit()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }  
  Serial.write(VERSION);
  Serial.write(AUTHOR);
}

void CommunicationLoop()
{
  char readByte = 0;
  while (Serial.available() > 0) 
  {
    readByte = Serial.read();
    protocol.Receive(readByte);
  }
}

// ------------------------------------

// Led section
// ------------------------------------


static uint8_t colorRed = 0xFF;
static uint8_t colorGreen = 0xFF;
static uint8_t colorBlue = 0xFF;
static bool isChanged = false;

void LedInit()
{
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear();
  isChanged = true;
}

void LedLoop()
{
  if (isChanged == true)
  {
      isChanged = false;
      for(int i=0; i<NUMPIXELS; i++) 
      {
        pixels.setPixelColor(i, pixels.Color(colorRed, colorGreen, colorBlue));
        pixels.show();   // Send the updated pixel colors to the hardware.
        delay(LED_DELAY);
      }
  }
}
// ------------------------------------

void setup() {
  LedInit();
  CommunicationInit();
}

void loop() {
  CommunicationLoop();
  LedLoop();
}
