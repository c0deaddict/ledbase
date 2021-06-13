#include <espbase.h>
#include "config.h"
#include "leds.h"

const RgbColor BLACK(0, 0, 0);

bool gammaCorrection = LED_DEFAULT_GAMMA_CORRECTION;
NeoGamma<NeoGammaTableMethod> colorGamma;

unsigned long long showDurationBuckets[] = {
    10, 20, 50, 100, 200, 500, 1000, 1500, 2000, 3000, 5000, 10000
};

Histogram showDuration(
    "esp_leds_show_duration",
    "Duration in microseconds of syncing the LEDs buffer to hardware",
    sizeof(showDurationBuckets) / sizeof(*showDurationBuckets),
    showDurationBuckets
);

RgbColor LedDriver::filter(RgbColor color) {
    if (gammaCorrection) {
        return colorGamma.Correct(color);
    } else {
        return color;
    }
}

void LedDriver::show() {
    unsigned long start = micros();
    render();
    unsigned long duration = micros() - start;
    showDuration.observe(duration);
}

void LedDriver::fill(RgbColor color) {
    for (int i = 0; i < LED_COUNT; i++) {
        buffer[i] = color;
    }
}

void LedDriver::clear() {
    fill(BLACK);
}

void LedDriver::off() {
    clear();
    show();
}

#if LED_DIM == 1

inline int LedDriver::map(int index) {
    if (index >= 0 && index < LED_COUNT) {
        return index;
    } else {
        return -1;
    }
}

#elif LED_DIM == 2

inline int LedDriver::map(int index) {
    int x = index % LED_XLEN;
    int y = index / LED_XLEN;
    return map(x, y);
}

#elif LED_DIM == 3

inline int LedDriver::map(int index) {
    int z = i / (LED_YLEN * LED_XLEN);
    int r = i % (LED_YLEN * LED_XLEN);
    int y = r / LED_XLEN;
    int x = r % LED_XLEN;
    return map(x, y, z);
}

#endif

Setting brightnessSetting(
    "brightness",
    [](JsonVariant& value) {
        value.set(LED_DEFAULT_BRIGHTNESS);
    },
    [](JsonVariant value) {
        int brightness = constrain(value.as<int>(), 0, 255);
        leds->setBrightness(brightness);
        return true;
    }
);

Setting gammaCorrectionSetting(
    "gammaCorrection",
    [](JsonVariant& value) {
        value.set(LED_DEFAULT_GAMMA_CORRECTION);
    },
    [](JsonVariant value) {
        gammaCorrection = value.as<bool>();
        return true;
    }
);
