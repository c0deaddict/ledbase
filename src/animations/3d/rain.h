#pragma once

#include <leds.h>
#include <animation.h>

#define MAX_DROPS ((LED_XLEN*LED_ZLEN)/3)

typedef struct {
    int8_t x, y, z;
} Drop;

class Rain : public Animation {
private:
    Drop drops[MAX_DROPS];
    void newDrop();
    byte hue = 0;

public:
    Rain() : Animation("rain", 25) {};
    void start();
    void tick();
    void beat();
};
