#include <espbase.h>
#include "config.h"
#include "motion_mode.h"
#include "animation.h"

MotionMode::MotionMode() : Mode("motion"), motionDuration(DEFAULT_MOTION_DURATION) {
    motionDurationSetting = new Setting(
        "motionDuration",
        [this](JsonObject &obj, const char *name) {
            obj[name] = motionDuration;
        },
        [this](JsonVariant value) {
            int newDuration = value.as<int>();
            if (newDuration <= 0) return false;
            motionDuration = newDuration;
            return true;
        }
    );
}

void MotionMode::enter() {
    motion = false;
    motionStart = 0;
    leds->off();
}

void MotionMode::leave() {
    stopAnimation();
}

void MotionMode::update() {
    if (motion) {
        if (millis() - motionStart > motionDuration*1000L) {
            motion = false;
            stopAnimation();
            leds->off();
        } else {
            animation->update();
        }
    }
}

void MotionMode::onMotionChange(bool motion) {
    Serial.printf("motion=%d\n\r", motion);
    if (motion) {
        if (!this->motion) {
            startAnimation();
        }
        this->motion = true;
        motionStart = millis();
    }
}
