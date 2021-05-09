#pragma once

#include <animation.h>

class Life : public Animation {
private:
    CRGB *cells1;
    CRGB *cells2;
    CRGB *currentGen;
    CRGB *nextGen;

    int gen;

    void seed();
    int countNeighbours(int idx, CRGB *avgColor);
    bool computeNextGen();

public:
    Life();
    void start();
    void stop();
    void tick();
    void draw();
};
