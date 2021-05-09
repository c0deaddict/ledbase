#pragma once

#include "leds.h"

class Palette {
public:
    const char *name;

    Palette(const char *name) : name(name) {};

    virtual CRGB color(uint8_t i);
};

class Palette16 : public Palette {
private:
    CRGBPalette16 data;

public:
    Palette16(const char *name, CRGBPalette16 data)
        : Palette(name)
        , data(data) {}

    CRGB color(uint8_t i) {
        return ColorFromPalette(data, i);
    }
};

extern Palette *palette;
extern Palette *palettesList[];

int registerPalette(Palette *palette);
bool isValidPalette(int idx);
void setPalette(int idx);
