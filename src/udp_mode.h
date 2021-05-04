#pragma once

#include <ledbase.h>

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
    void onData(byte *data, size_t len);
};

extern void setLogicalPixel(int i, CRGB color);
