#include <espbase.h>
#include "config.h"
#include "animation.h"

Animation* animationsList[MAX_ANIMATIONS] = { NULL, };

// TODO: define a single RGB color value, define a palette 0 = single color
// TODO: define intensity parameter that determines the speed of animations.
// TODO: run most animations at a fixed FPS (configurable).

class NullAnimation : public Animation {
public:
    NullAnimation() : Animation("null", 0) {};
    void tick() {};
};

Animation *animation = new NullAnimation();

bool started = false;

Setting animationSetting(
    "animation",
    [](JsonVariant& value) {
        value.set(0);
    },
    [](JsonVariant value) {
        int animationIdx = value.as<int>();
        if (!isValidAnimation(animationIdx)) return false;
        setAnimation(animationIdx);
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
