#include <espbase.h>
#include "config.h"
#include "palette.h"

// Palette16 rainbow("rainbow", RainbowColors_p);
// Palette16 rainbowStripe("rainbow_stripe", RainbowStripeColors_p);
// Palette16 cloud("cloud", CloudColors_p);
// Palette16 lava("lava", LavaColors_p);
// Palette16 ocean("ocean", OceanColors_p);
// Palette16 forest("forest", ForestColors_p);
// Palette16 party("party", PartyColors_p);
// Palette16 heat("heat", HeatColors_p);

class RainbowPalette : public Palette {
public:
    RainbowPalette() : Palette("rainbow") {};

    RgbColor color(float index) {
        return HsbColor(index, 1.0f, 1.0f);
    }
};

RainbowPalette rainbow;

Palette* palettesList[MAX_PALETTES] = { &rainbow, };

int paletteIdx = 0;
Palette *palette = palettesList[paletteIdx];

Setting paletteSetting(
    "palette",
    [](JsonObject &obj, const char *name) {
        obj[name] = paletteIdx;
    },
    [](JsonVariant value) {
        int idx = value.as<int>();
        if (!isValidPalette(idx)) return false;
        setPalette(idx);
        return true;
    }
);

int registerPalette(Palette *palette) {
    for (int idx = 0; idx < MAX_PALETTES; idx++) {
        if (palettesList[idx] == NULL) {
            palettesList[idx] = palette;
            return idx;
        }
    }

    return -1;
}

bool isValidPalette(int idx) {
    if (idx < 0 || idx >= MAX_PALETTES) {
        return false;
    }
    return palettesList[idx] != NULL;
}

void setPalette(int idx) {
    if (!isValidPalette(idx)) return;
    paletteIdx = idx;
    palette = palettesList[idx];
}
