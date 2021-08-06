#if LED_DIM == 2
#include "wave.h"

#define CENTER_X (LED_XLEN / 2)
#define CENTER_Y (LED_YLEN / 2)

float wave(float w, float k, float t, float x, float y) {
    float r = sqrt(pow(x, 2) + pow(y, 2));
    return cos(k * r + w * t);
}

void Wave::draw() {
    // TODO: update
    float t = (millis() / 10000.0) * (float)intensity;
    float w = 0.5;
    float k = -w;
    for (int x = 0; x < LED_XLEN; x++) {
        for (int y = 0; y < LED_YLEN; y++) {
            float h = 128.0 + 127.0 * wave(w, k, t, x - CENTER_X, y - CENTER_Y);
            leds->setPixel(x, y, HsbColor((float)h / 255.0f, 1.0f, 1.0f));
        }
    }
}
#endif
