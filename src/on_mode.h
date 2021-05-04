#pragma once

#include "mode.h"
#include "leds.h"
#include "animation.h"

class OnMode : public Mode {
public:
    OnMode() : Mode("on") {};

    void enter() {
        ledsOff();
        startAnimation();
    }

    void leave() {
        stopAnimation();
    }

    void update() {
        animation->update();
    }
};
