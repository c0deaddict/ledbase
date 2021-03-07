#include "config.h"
#include "motion_mode.h"
#include "animation.h"
#include "settings.h"

MotionMode::MotionMode() : Mode("motion"), motionDuration(DEFAULT_MOTION_DURATION) {
    motionDurationSetting = new Setting(
        "motionDuration",
        [](JsonVariant& value) {
            value.set(DEFAULT_MOTION_DURATION);
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
    ledsOff();
}

void MotionMode::update() {
    if (motion) {
        if (millis() - motionStart > motionDuration*1000L) {
            motion = false;
            animation->stop();
            ledsOff();
        } else {
            animation->update();
        }
    }
}

void MotionMode::onMotionChange(bool motion) {
    Serial.printf("motion=%d\n\r", motion);
    if (motion) {
        if (this->motion != motion) {
            this->motion = motion;
            animation->start();
        }
        motionStart = millis();
    }
}
