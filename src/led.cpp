#include "led.h"

void Led::Init()
{
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  m_pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  m_pixels.clear();
  isChanged = true;
}

void Led::Loop()
{
  if (isChanged == true)
  {
      isChanged = false;
      for(int i=0; i<LED_COUNT; ++i)
      {
        m_pixels.setPixelColor(i, m_pixels.Color(colorRed, colorGreen, colorBlue));
        m_pixels.show();   // Send the updated pixel colors to the hardware.
        delay(LED_DELAY);
      }
  }

}
