#pragma once

#include <espbase.h>
#include "mode.h"
#include "leds.h"

class UdpMode : public Mode {
private:
    bool active;
    unsigned long lastFrameTime;
    unsigned int timeout;
    Setting *timeoutSetting;

    unsigned int beatDuration;
    unsigned long beatStart;
    CRGB beatColor;

    void frame(byte flags, byte *data, size_t len);
    void beat(byte flags, byte *data, size_t len);

public:
    UdpMode();

    void enter();
    void update();
    void onFrame(byte *data, size_t len);
    bool onBeat(byte *data, size_t len);
};

extern void setLogicalPixel(int i, CRGB color);
