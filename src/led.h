#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

///
#define LED_DELAY 25 // Time (in milliseconds) to pause between pixels
///
#define LED_COUNT 50
/// control pin
#define PIN        A5

class Led
{
    public:
        ~Led() {}

        void Init();
        void Refresh();
        void SetColor(uint16_t position, uint8_t red, uint8_t green, uint8_t blue);
        void SetColorAll(uint8_t red, uint8_t green, uint8_t blue);
        /// Getter of singleton
        static Led & GetInstance()
        {
            static Led led;
            return led;
        }

    private:
        bool isChanged = false;
        uint8_t colorRed = 0xFF;
        uint8_t colorGreen = 0xFF;
        uint8_t colorBlue = 0xFF;
        /// Create driver
        Adafruit_NeoPixel m_pixels = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

        Led() {}
};

