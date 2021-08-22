#include "walk.h"

Walk::Walk() : Animation("walk"), offset(0.0f) {
};

void Walk::draw() {
    leds->clear();

    float count = intensity * 3.0f;
    float size = float(LED_COUNT) / count;

    for (int i = 0; i < LED_COUNT; i++) {
        float x = fmod(float(i) - offset, LED_COUNT);
        if (x < 0) {
            x = float(LED_COUNT) + x;
        }
        float d = x / size;
        float hue = floor(d) * (1.0 / count);
        float brightness = pow(fmod(d, 1.0), 2.0);
        HsbColor color(hue, 1.0f, brightness);
        leds->setPixel(i, color);
    }

    offset = fmod(offset + speed, float(LED_COUNT));
}
