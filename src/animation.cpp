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

int animationIdx = 0;
Animation *animation = new NullAnimation();
float intensity = DEFAULT_INTENSITY;
RgbColor color = DEFAULT_COLOR;

bool started = false;

Setting animationSetting(
    "animation",
    [](JsonDocument &doc, const char *name) {
        doc[name] = animationIdx;
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
    [](JsonDocument& doc, const char *name) {
        doc[name] = intensity;
    },
    [](JsonVariant value) {
        float newIntensity = value.as<float>();
        if (newIntensity < 0) {
            return false;
        }
        intensity = newIntensity;
        return true;
    }
);

bool setColor(const char *str) {
    unsigned int r, g, b;
    if (str == NULL || sscanf(str, "%02x%02x%02x", &r, &g, &b) != 3) {
        return false;
    }
    color = RgbColor(r, g, b);
    return true;
}

Setting colorSetting(
    "color",
    [](JsonDocument &doc, const char *name) {
        char buf[7];
        sprintf(buf, "%02x%02x%02x", color.R, color.G, color.B);
        doc[name] = String(buf);
    },
    [](JsonVariant value) {
        return setColor(value.as<const char *>());
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
    animationIdx = idx;
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
