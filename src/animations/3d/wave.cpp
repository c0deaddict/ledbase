#if LED_DIM == 3
#include "wave.h"

float wave(float w, float k, float t, float x, float z) {
    float r = sqrt(pow(x, 2) + pow(z, 2));
    return cos(k * r + w * t);
}

void Wave::draw() {
    fillColor(CRGB::Black);

    float t = (millis() / 10000.0) * (float)intensity;
    float w = 1.5;
    float k = -w;
    float maxx = LED_XLEN - 1;
    float maxy = LED_YLEN - 1;
    float maxz = LED_ZLEN - 1;

    for (int x = 0; x < LED_XLEN; x++) {
        for (int z = 0; z < LED_ZLEN; z++) {
            float vx = x - maxx / 2.0;
            float vz = z - maxz / 2.0;
            float v = wave(w, k, t, vx, vz);
            float y = round(maxy - ((maxy/2.0) + (maxy/2.0) * v));
            setPixel(x, y, z, CHSV(255 * (y / maxy), 255, 255));
        }
    }
}
#endif
