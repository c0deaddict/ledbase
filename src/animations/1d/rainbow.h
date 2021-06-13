#pragma once

#include <animation.h>

class Rainbow : public Animation {
private:
    float offset;

public:
    Rainbow();
    void tick();
    void draw();
};
