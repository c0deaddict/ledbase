#pragma once

#include <leds.h>
#include <animation.h>

class Cubes : public Animation {
private:
    int t;
    void fillBox(int x1, int y1, int z1, int x2, int y2, int z2, RgbColor color);
    void drawCube(int offset, int y, RgbColor color);

public:
    Cubes();
    void start();
    void tick();
};
