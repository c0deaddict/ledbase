#include <palette.h>
#include "rainbow.h"

Rainbow::Rainbow() : Animation("rainbow") {
    setIntensityScalar(5.0);
};

void Rainbow::tick() {
    offset += 1.0f / LED_COUNT;
}

void Rainbow::draw() {
    float hue = offset;
    for (int i = 0; i < LED_COUNT; i++) {
        hue += 1.0f / LED_COUNT;
        leds->setPixel(i, palette->color(fmod(hue, 1.0f)));
    }
}
