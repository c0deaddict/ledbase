#pragma once

#include <config.h>
#include <animation.h>

class Random : public Animation {
public:
    Random() : Animation("random") {};
    void tick();
};
