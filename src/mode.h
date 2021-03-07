#pragma once

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

    // Called when data is received.
    virtual void onData(byte *data, size_t len) {};

    virtual void onMotionChange(bool motion) {};

    virtual void onFft(double *peaks, size_t count) {};
};

extern Mode *mode;
extern Mode *modesList[];

int registerMode(Mode *mode);
bool isValidMode(int idx);
void setMode(int idx);
