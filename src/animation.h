#pragma once

#include "leds.h"

class Animation {
private:
    unsigned long last_frame;

protected:
    int fps;

public:
    const char *name;

    Animation(const char *name, int fps) : last_frame(0), fps(fps), name(name) {};

    virtual void start() {};
    virtual void stop() {};
    virtual void tick() = 0;

    void update() {
        if (millis() - last_frame > 1000.0 / fps) {
            last_frame = millis();
            tick();
            showLeds();
        }
    }
};

extern Animation *animation;
extern Animation *animationsList[];

int registerAnimation(Animation *animation);
bool isValidAnimation(int idx);
void setAnimation(int idx);
