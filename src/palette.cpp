#include <espbase.h>
#include "config.h"
#include "palette.h"

// FastLED builtin palettes.
Palette16 rainbow("rainbow", RainbowColors_p);
Palette16 rainbowStripe("rainbow_stripe", RainbowStripeColors_p);
Palette16 cloud("cloud", CloudColors_p);
Palette16 lava("lava", LavaColors_p);
Palette16 ocean("ocean", OceanColors_p);
Palette16 forest("forest", ForestColors_p);
Palette16 party("party", PartyColors_p);
Palette16 heat("heat", HeatColors_p);

Palette* palettesList[MAX_PALETTES] = {
    &rainbow,
    &rainbowStripe,
    &cloud,
    &lava,
    &ocean,
    &forest,
    &party,
    &heat,
    NULL,
};

Palette *palette = palettesList[0];

Setting paletteSetting(
    "palette",
    [](JsonVariant& value) {
        value.set(0);
    },
    [](JsonVariant value) {
        int paletteIdx = value.as<int>();
        if (!isValidPalette(paletteIdx)) return false;
        setPalette(paletteIdx);
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
    palette = palettesList[idx];
}
