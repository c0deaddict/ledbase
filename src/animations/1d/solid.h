#pragma once

#include <espbase.h>
#include <animation.h>

class Solid : public Animation {
private:
    uint8_t palIndex;
    Setting *palIndexSetting;

public:
    Solid();
    void draw();
};
