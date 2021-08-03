#include <palette.h>
#include "rainbow.h"

// TODO: speed and intensity should be equal across devices.
// eg. don't divide by LED_COUNT but by a fixed amount.

// 4 seconds to move rainbow across entire strip.
const float speedMultiplier = 0.25f;

Rainbow::Rainbow() : Animation("rainbow") {
};

void Rainbow::draw() {
    float scale = 1.0f / LED_COUNT;
    float step = scale * intensity;
    float hue = offset;
    for (int i = 0; i < LED_COUNT; i++, hue += step) {
        leds->setPixel(i, palette->color(fmod(hue, 1.0f)));
    }
    offset = fmod(offset + scale * speed * speedMultiplier, 1.0f);
}
