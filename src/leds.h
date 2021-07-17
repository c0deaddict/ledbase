#pragma once

#include <NeoPixelBus.h>

extern const RgbColor BLACK;

class LedDriver {
protected:
    byte brightness = 255;
    RgbColor buffer[LED_COUNT] = {BLACK, };

    virtual void render() = 0;

    virtual int map(int index);
    #if LED_DIM == 2
    virtual int map(int x, int y) = 0;
    #elif LED_DIM == 3
    virtual int map(int x, int y, int z) = 0;
    #endif

    RgbColor filter(RgbColor color);

public:
    virtual void setup();

    void setBrightness(byte brightness) {
        this->brightness = brightness;
    }

    byte getBrightness() {
        return brightness;
    }

    void show();
    void fill(RgbColor color);
    void clear();
    void off();

    inline void setPixel(int i, RgbColor color) {
        int idx = map(i);
        if (idx >= 0) {
            buffer[idx] = color;
        }
    }

    inline RgbColor getPixel(int i) {
        int idx = map(i);
        if (idx >= 0) {
            return buffer[idx];
        } else {
            return BLACK;
        }
    }

    #if LED_DIM == 2

    inline void setPixel(int x, int y, RgbColor color) {
        int idx = map(x, y);
        if (idx >= 0) {
            buffer[idx] = color;
        }
    }

    inline RgbColor getPixel(int x, int y) {
        int idx = map(x, y);
        if (idx >= 0) {
            return buffer[idx];
        } else {
            return BLACK;
        }
    }

    #elif LED_DIM == 3

    inline void setPixel(int x, int y, int z, RgbColor color) {
        int idx = map(x, y, z);
        if (idx >= 0) {
            buffer[idx] = color;
        }
    }

    inline RgbColor getPixel(int x, int y, int z) {
        int idx = map(x, y, z);
        if (idx >= 0) {
            return buffer[idx];
        } else {
            return BLACK;
        }
    }

    #endif

    inline void setRawPixel(int i, RgbColor color) {
        if (i >= 0 && i < LED_COUNT) {
            buffer[i] = color;
        }
    }

    inline RgbColor getRawPixel(int i) {
        if (i >= 0 && i < LED_COUNT) {
            return buffer[i];
        } else {
            return BLACK;
        }
    }
};

extern LedDriver *leds;
