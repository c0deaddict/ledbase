#include <palette.h>
#include "solid.h"

Solid::Solid(int fps)
    : Animation("solid", fps)
    , palIndex(0) {
    palIndexSetting = new Setting(
        "solidPalIndex",
        [](JsonVariant& value) {
            value.set(0);
        },
        [this](JsonVariant value) {
            int newIndex = value.as<int>();
            if (newIndex < 0 || newIndex > 255) return false;
            palIndex = newIndex;
            return true;
        }
    );
}

void Solid::tick() {
    fillColor(palette->color(palIndex));
}
