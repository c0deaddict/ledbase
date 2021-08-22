#include "random.h"

void Random::draw() {
    // TODO: take speed/intensity into consideration.
    int i = random(LED_COUNT);
    RgbColor color(random(256), random(256), random(256));
    leds->setRawPixel(i, color);
}
