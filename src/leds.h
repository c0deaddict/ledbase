#pragma once

#include <NeoPixelBus.h>

// TODO:
// for brightness+gamma correction
// need another buffer
//
// could use NeoBufferContext for this. the buffer needs to be defined by the
// client, since it relies on the Feature type parameter.
//
// translation of logical to raw should be done on the buffer.
// before each show, the buffer can be copied into the actual strip(s) with the Blt method.

class LedDriver {
private:
    virtual void _show() = 0;
    virtual void _setRawPixel(uint16_t index, RgbColor color) = 0;
    virtual void _setLogicalPixel(int index, RgbColor color);
    virtual RgbColor _getLogicalPixel(int index);

public:
    virtual void setup();
    void setRawPixel(uint16_t index, RgbColor color);
    virtual RgbColor getRawPixel(uint16_t index) = 0;

    virtual void setBrightness(byte brightness) = 0;

    virtual void fill(RgbColor color);

    void show();
    void clear();
    void off();

    void setPixel(int i, RgbColor color);
    RgbColor getPixel(int i);

    virtual void setPixel(int x, int y, RgbColor color) {};
    virtual RgbColor getPixel(int x, int y);
    virtual void setPixel(int x, int y, int z, RgbColor color) {};
    virtual RgbColor getPixel(int x, int y, int z);
};

extern LedDriver *leds;
