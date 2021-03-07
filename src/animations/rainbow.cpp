#include "rainbow.h"

void Rainbow::tick() {
   uint8_t hue = beat8(60, 255);
   fill_rainbow(leds, LED_COUNT, hue, 10);
}
