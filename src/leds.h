#pragma once

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
