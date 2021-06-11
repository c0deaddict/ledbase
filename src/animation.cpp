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
RgbColor color = DEFAULT_COLOR;

bool started = false;

Setting animationSetting(
    "animation",
    [](JsonVariant& value) {
        value.set(0);
    },
    [](JsonVariant value) {
        int idx = value.as<int>();
        if (!isValidAnimation(idx)) return false;
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

Setting colorSetting(
    "color",
    [](JsonVariant& value) {
        char buf[7];
        sprintf(buf, "%02x%02x%02x", color.R, color.G, color.B);
        value.set(String(buf));
    },
    [](JsonVariant value) {
        unsigned int r, g, b;
        const char *str = value.as<const char *>();
        if (str == NULL || sscanf(str, "%02x%02x%02x", &r, &g, &b) != 3) {
            return false;
        }
        color = RgbColor(r, g, b);
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

int lookupAnimation(const char *name, size_t len) {
    for (int idx = 0; idx < MAX_ANIMATIONS; idx++) {
        Animation *animation = animationsList[idx];
        if (animation != NULL) {
            if (!strncmp(name, animation->name, len)) {
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
