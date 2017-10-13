#include <FastLED.h>

#if defined ARDUINO_ESP8266_ESP01
#define LED_PIN     2
#else
#define LED_PIN     D3
#endif

#define NUM_LEDS    147
#define BRIGHTNESS  20
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

#define FULL_CYCLE_MINUTES_LOWER 10
#define FULL_CYCLE_MINUTES_UPPER 20

CRGB leds[NUM_LEDS];

void FillLEDsFromPaletteColors(uint8_t colorIndex);

void setup()
{
    delay(1000);
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    Serial.begin(9600);
}

int delayMilliseconds;
void loop()
{
    static uint8_t startIndex = 0;
    FillLEDsFromPaletteColors(startIndex);
    FastLED.show();
    
    if (startIndex == 0) {
      delayMilliseconds = 1000*60*random(FULL_CYCLE_MINUTES_LOWER, FULL_CYCLE_MINUTES_UPPER)/255;
    }
    FastLED.delay(delayMilliseconds);
    startIndex += 1;
}

void FillLEDsFromPaletteColors(uint8_t colorIndex)
{
    uint8_t brightness = 255;
    float newColorIndex = colorIndex;
    float colorIndexIncrement = 0.9;
    for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette(RainbowColors_p, int(newColorIndex), brightness, LINEARBLEND);
        if (i < NUM_LEDS / 2) {
          newColorIndex += colorIndexIncrement;
        } else {
          newColorIndex -= colorIndexIncrement;
        }
    }
}
