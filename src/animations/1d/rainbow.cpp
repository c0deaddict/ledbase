#include <palette.h>
#include "rainbow.h"

Rainbow::Rainbow() : Animation("rainbow") {
    setIntensityScalar(5.0);
};

void Rainbow::tick() {
    palIndex++;
}

void Rainbow::draw() {
    for (int i = 0; i < LED_COUNT; i++) {
        byte hue = palIndex + i*5;
        leds->setPixel(i, palette->color((float)hue / 255.0f));
    }
}
