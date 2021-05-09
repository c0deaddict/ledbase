#pragma once

#include <animation.h>

class Rainbow : public Animation {
private:
    uint8_t palIndex;

public:
    Rainbow();
    void tick();
    void draw();
};
