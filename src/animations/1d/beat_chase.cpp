#include "beat_chase.h"

void BeatChase::tick() {
    // Shift all LED's to the right.
    for (int i = LED_COUNT - 1; i > 0; i--) {
        leds->setPixel(i, leds->getPixel(i - 1));
    }
}

void BeatChase::draw() {
    RgbColor color = RgbColor(0, 0, 0);
    if (energy > 0) {
        float ratio = energy / (float)peakEnergy;
        byte brightness = constrain(round(pow(ratio, 1.5) * 255), 0, 255);
        color = HsbColor((float)hue / 255.0f, 1.0f, (float)brightness / 255.0f);
        energy--;
    }

    leds->setPixel(0, color);
}

void BeatChase::beat() {
    hue += 5;
    energy = peakEnergy;
}
