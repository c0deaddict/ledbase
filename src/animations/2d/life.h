#pragma once

#include <animation.h>

class Life : public Animation {
private:
    RgbColor *cells1;
    RgbColor *cells2;
    RgbColor *currentGen;
    RgbColor *nextGen;

    int gen;

    void seed();
    int countNeighbours(int idx, RgbColor *avgColor);
    bool computeNextGen();

public:
    Life();
    void start();
    void stop();
    void tick();
    void draw();
};
