#pragma once

#include "leds.h"

class Palette {
public:
    const char *name;

    Palette(const char *name) : name(name) {};

    virtual RgbColor color(float index);
};

extern Palette *palette;
extern Palette *palettesList[];

int registerPalette(Palette *palette);
bool isValidPalette(int idx);
void setPalette(int idx);
