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

int paletteIdx = 0;
std::vector<Palette *> palettes = { &rainbow };
Palette *palette = palettes[paletteIdx];

Setting paletteSetting(
    "palette",
    [](JsonObject &obj, const char *name) {
        obj[name] = paletteIdx;
    },
    [](JsonVariant value) {
        int idx = value.as<int>();
        return setPalette(idx);
    }
);

int registerPalette(Palette *palette) {
    palettes.push_back(palette);
    return palettes.size() - 1;
}

bool setPalette(int idx) {
    if (idx < 0 || idx >= (int)palettes.size()) {
        return false;
    }
    paletteIdx = idx;
    palette = palettes[idx];
    return true;
}
