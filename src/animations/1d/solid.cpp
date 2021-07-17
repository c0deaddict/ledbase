#include "solid.h"

Solid::Solid() : Animation("solid", FPS) {
}

void Solid::draw() {
    leds->fill(color);
}
