#pragma once

#include <vector>
#include "leds.h"

class Palette {
public:
    const char *name;

    Palette(const char *name) : name(name) {};

    virtual RgbColor color(float index);
};

extern Palette *palette;
extern std::vector<Palette *> palettes;

int registerPalette(Palette *palette);
bool setPalette(int idx);
