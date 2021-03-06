#pragma once

#include <espbase.h>
#include "mode.h"

class MotionMode : public Mode {
private:
    bool motion;
    unsigned long motionStart;
    unsigned int motionDuration;
    Setting *motionDurationSetting;

public:
    MotionMode();

    void enter();
    void leave();
    void update();
    void onMotionChange(bool motion);
};
