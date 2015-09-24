// This example shows the use of INSTANT_OPTIONS_MODE
// When set it stops the text routine from having to scroll all
// of the existing text off the display before changing the scroll
// direction.
#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>

#include <LEDMatrix.h>
#include <LEDText.h>
#include <FontMatrise.h>

// Change the next 6 defines to match your matrix type and size

#define LED_PIN        6
#define COLOR_ORDER    GRB
#define CHIPSET        WS2811_400

#define MATRIX_WIDTH   -40  // Set this negative if physical led 0 is opposite to where you want logical 0
#define MATRIX_HEIGHT  7    // Set this negative if physical led 0 is opposite to where you want logical 0
#define MATRIX_TYPE    HORIZONTAL_ZIGZAG_MATRIX  // See top of LEDMatrix.h for matrix wiring types
#define BRIGHTNESS     15   //  My LEDs are super bright. Not sure about yours.

cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;

cLEDText ScrollingMsg;

const unsigned char TxtDemo[] = { EFFECT_FRAME_RATE "\x00"
                                  EFFECT_HSV_AH "\x00\xff\xff\xff\xff\xff"
                                  EFFECT_SCROLL_LEFT "   The "
                                  EFFECT_SCROLL_UP "Quick "
                                  EFFECT_SCROLL_LEFT "Brown "
                                  EFFECT_SCROLL_DOWN "Fox"
                                  EFFECT_SCROLL_LEFT "Jumps "
                                  EFFECT_SCROLL_UP "Over  "
                                  EFFECT_SCROLL_LEFT "The "
                                  EFFECT_SCROLL_DOWN "Lazy  "
                                  EFFECT_SCROLL_LEFT "Dog " };
uint16_t Options;

void setup()
{
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds[0], leds.Size());
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear(true);
  delay(500);
  FastLED.showColor(CRGB::Red);
  delay(1000);
  FastLED.showColor(CRGB::Lime);
  delay(1000);
  FastLED.showColor(CRGB::Blue);
  delay(1000);
  FastLED.showColor(CRGB::White);
  delay(1000);
  FastLED.show();

  ScrollingMsg.SetFont(MatriseFontData);
  ScrollingMsg.Init(&leds, leds.Width(), ScrollingMsg.FontHeight() + 1, 0, 0);
  ScrollingMsg.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
  ScrollingMsg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, 0xff, 0x00, 0xff);
  Options = INSTANT_OPTIONS_MODE;
  ScrollingMsg.SetOptionsChangeMode(Options);
}


void loop()
{
  if (ScrollingMsg.UpdateText() == -1)
  {
    ScrollingMsg.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
    Options ^= INSTANT_OPTIONS_MODE;
    ScrollingMsg.SetOptionsChangeMode(Options);
  }
  else
    FastLED.show();
  delay(10);
}

