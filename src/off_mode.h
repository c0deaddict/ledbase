#pragma once

#include "mode.h"
#include "leds.h"

class OffMode : public Mode {
public:
    OffMode() : Mode("off") {};

    void enter() {
        leds->off();
    }
};
