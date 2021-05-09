#pragma once

#include <animation.h>

class Random : public Animation {
public:
    Random() : Animation("random", 60) {};
    void tick();
};
