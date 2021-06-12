#include <espbase.h>
#include "config.h"
#include "leds.h"

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

void LedDriver::_setLogicalPixel(int index, RgbColor color) {
    setRawPixel(index, color);
}

RgbColor LedDriver::_getLogicalPixel(int index) {
    return getRawPixel(index);
}

void LedDriver::fill(RgbColor color) {
    for (uint16_t i = 0; i < LED_COUNT; i++) {
        setRawPixel(i, color);
    }
}

void LedDriver::clear() {
    fill(RgbColor(0, 0, 0));
}

void LedDriver::off() {
    clear();
    show();
}

void LedDriver::show() {
    unsigned long start = micros();
    _show();
    unsigned long duration = micros() - start;
    showDuration.observe(duration);
}

void LedDriver::setRawPixel(uint16_t index, RgbColor color) {
    if (gammaCorrection) {
        color = colorGamma.Correct(color);
    }
    _setRawPixel(index, color);
}

void LedDriver::setPixel(int i, RgbColor color) {
    if (i >= 0 && i < LED_COUNT) {
        _setLogicalPixel(i, color);
    }
}

RgbColor LedDriver::getPixel(int i) {
    if (i >= 0 && i < LED_COUNT) {
        return _getLogicalPixel(i);
    } else {
        return RgbColor(0, 0, 0);
    }
}

RgbColor LedDriver::getPixel(int x, int y) {
    return RgbColor(0, 0, 0);
}

RgbColor LedDriver::getPixel(int x, int y, int z) {
    return RgbColor(0, 0, 0);
}

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
