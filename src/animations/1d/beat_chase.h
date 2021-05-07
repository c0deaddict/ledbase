#pragma once

#include <animation.h>

class BeatChase : public Animation {
private:
    byte hue;
    int peakEnergy;
    int energy;

public:
    BeatChase(int energy, int fps)
        : Animation("beat_chase", fps)
        , peakEnergy(energy) {};
    void tick();
    void beat();
};
