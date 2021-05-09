#include <espbase.h>
#include "config.h"
#include "animation.h"

Animation* animationsList[MAX_ANIMATIONS] = { NULL, };

// TODO: define a single RGB color value, define a palette 0 = single color

class NullAnimation : public Animation {
public:
    NullAnimation() : Animation("null", 0) {};
    void draw() {};
};

Animation *animation = new NullAnimation();
uint8_t intensity = DEFAULT_INTENSITY;

bool started = false;

Setting animationSetting(
    "animation",
    [](JsonVariant& value) {
        value.set(0);
    },
    [](JsonVariant value) {
        int idx;
        if (value.is<String>()) {
            idx = lookupAnimation(value.as<String>().c_str());
            if (idx < 0) return false;
        } else {
            idx = value.as<int>();
            if (!isValidAnimation(idx)) return false;
        }
        setAnimation(idx);
        return true;
    }
);

Setting intensitySetting(
    "intensity",
    [](JsonVariant& value) {
        value.set(DEFAULT_INTENSITY);
    },
    [](JsonVariant value) {
        int newIntensity = value.as<int>();
        if (newIntensity < 0 || newIntensity > 255) {
            return false;
        }
        intensity = newIntensity;
        return true;
    }
);

int registerAnimation(Animation *animation) {
    for (int idx = 0; idx < MAX_ANIMATIONS; idx++) {
        if (animationsList[idx] == NULL) {
            animationsList[idx] = animation;
            return idx;
        }
    }

    return -1;
}

bool isValidAnimation(int idx) {
    if (idx < 0 || idx >= MAX_ANIMATIONS) {
        return false;
    }
    return animationsList[idx] != NULL;
}

int lookupAnimation(const char *name) {
    for (int idx = 0; idx < MAX_ANIMATIONS; idx++) {
        Animation *animation = animationsList[idx];
        if (animation != NULL) {
            if (!strcmp(name, animation->name)) {
                return idx;
            }
        }
    }
    return -1;
}

void setAnimation(int idx) {
    if (!isValidAnimation(idx)) return;

    // TODO: consider transitions, like fade?
    if (started) animation->stop();
    animation = animationsList[idx];
    if (started) animation->start();
}

void startAnimation() {
    if (!started) {
        animation->start();
        started = true;
    }
}

void stopAnimation() {
    if (started) {
        animation->stop();
        started = false;
    }
}
