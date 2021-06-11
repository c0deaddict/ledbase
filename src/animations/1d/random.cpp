#include "random.h"

void Random::tick() {
    int i = random(LED_COUNT);
    RgbColor color(random(256), random(256), random(256));
    leds->setRawPixel(i, color);
}
