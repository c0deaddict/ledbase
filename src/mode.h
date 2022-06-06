#pragma once

#include <vector>
#include <Arduino.h>

class Mode {
public:
    const char *name;

    Mode(const char *name) : name(name) {};

    // Called on entering mode.
    virtual void enter() {};

    // Called on mode exit.
    virtual void leave() {};

    // Called each loop.
    virtual void update() {};

    // Called when an UDP frame is received.
    virtual void onFrame(byte *data, size_t len) {};

    // Called when an UDP beat is received.
    // Return false means pass the beat onto the animation.
    virtual bool onBeat(byte *data, size_t len) {
        return false;
    };

    virtual void onMotionChange(bool motion) {};

    virtual void onFft(double *peaks, size_t count) {};
};

extern Mode *mode;
extern std::vector<Mode *> modes;

int registerMode(Mode *mode);
int lookupMode(const char *name, size_t len);
bool setMode(int idx);
