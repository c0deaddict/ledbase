#include <palette.h>
#include "rainbow.h"

void Rainbow::tick() {
   uint8_t palIndex = beat8(60, 255);
   for (int i = 0; i < LED_COUNT; i++) {
       leds[i] = palette->color(palIndex);
       palIndex += 5;
   }
}
