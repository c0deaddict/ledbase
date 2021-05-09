#pragma once

#define FASTLED_INTERNAL //remove annoying pragma messages
#include <FastLED.h>

FASTLED_USING_NAMESPACE

extern CRGB leds[LED_COUNT];

bool showLeds();
bool ensureShowLeds();
void fillColor(CRGB color);
void setBrightness(byte brightness);
void clearLeds();
void ledsOff();

extern void configureLeds();

#if LED_DIM == 1
extern void setPixel(int i, CRGB color);
#elif LED_DIM == 2
extern void setPixel(int x, int y, CRGB color);
#elif LED_DIM == 3
extern void setPixel(int x, int y, int z, CRGB color);
#endif
