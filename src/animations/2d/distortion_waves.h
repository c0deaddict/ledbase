#pragma once

#include <animation.h>

class DistortionWaves : public Animation {
public:
    DistortionWaves() : Animation("distortion_waves") {};
    void draw();
};
