#include "beat_chase.h"

void BeatChase::tick() {
    // Shift all LED's to the right.
    for (int i = LED_COUNT - 1; i > 0; i--) {
        leds[i] = leds[i - 1];
    }
}

void BeatChase::draw() {
    if (energy > 0) {
        float ratio = energy / (float)peakEnergy;
        byte brightness = constrain(round(pow(ratio, 1.5) * 255), 0, 255);
        leds[0] = CHSV(hue, 255, brightness);
        energy--;
    } else {
        leds[0] = CRGB::Black;
    }
}

void BeatChase::beat() {
    hue += 5;
    energy = peakEnergy;
}
