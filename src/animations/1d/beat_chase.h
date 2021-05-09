#pragma once

#include <animation.h>

class BeatChase : public Animation {
private:
    byte hue;
    int peakEnergy;
    int energy;

public:
    BeatChase(int energy)
        : Animation("beat_chase")
        , peakEnergy(energy) {};
    void tick();
    void draw();
    void beat();
};
