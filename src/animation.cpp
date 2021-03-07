#include "config.h"
#include "animation.h"
#include "settings.h"

#include "animations/rainbow.h"

Animation* animationsList[MAX_ANIMATIONS] = {
    new Rainbow(60),
    NULL,
};

Animation *animation = animationsList[0];

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

    // TODO: are we running an animation?
    // TODO: consider transitions, like fade?
    animation->stop();
    animation = animationsList[idx];
    animation->start();
}
