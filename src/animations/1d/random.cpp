#include "random.h"

void Random::tick() {
    int i = random(LED_COUNT);
    leds[i] = CRGB(random(256), random(256), random(256));
}
