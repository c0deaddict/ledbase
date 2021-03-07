#pragma once

#include <animation.h>

class Rainbow : public Animation {
public:
    Rainbow(int fps) : Animation("rainbow", fps) {};
    void tick();
};
