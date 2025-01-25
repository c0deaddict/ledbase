#include <espbase.h>
#include "config.h"
#include "animation.h"

class NullAnimation : public Animation {
public:
    NullAnimation() : Animation("null", 0) {};
    void draw() {};
};

int animationIdx = 0;
Animation *nullAnimation = new NullAnimation();
Animation *animation = nullAnimation;
std::vector<Animation *> animations = {};

float intensity = DEFAULT_INTENSITY;
float speed = DEFAULT_SPEED;
RgbColor color = DEFAULT_COLOR;

bool started = false;

void ledsStateUpdated();

Setting animationSetting(
    "animation",
    [](JsonObject &obj, const char *name) {
        obj[name] = animationIdx;
    },
    [](JsonVariant value) {
        int idx = value.as<int>();
        bool ok = setAnimation(idx);
        if (ok) ledsStateUpdated();
        return ok;
    }
);

Setting intensitySetting(
    "intensity",
    [](JsonObject &obj, const char *name) {
        obj[name] = intensity;
    },
    [](JsonVariant value) {
        bool ok = setIntensity(value.as<float>());
		if (ok) ledsStateUpdated();
    }
);

Setting speedSetting(
    "speed",
    [](JsonObject &obj, const char *name) {
        obj[name] = speed;
    },
    [](JsonVariant value) {
        float newSpeed = value.as<float>();
        if (newSpeed < 0) {
            return false;
        }
        speed = newSpeed;
        ledsStateUpdated();
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
    [](JsonObject &obj, const char *name) {
        char buf[7];
        sprintf(buf, "%02x%02x%02x", color.R, color.G, color.B);
        obj[name] = String(buf);
    },
    [](JsonVariant value) {
        bool ok = setColor(value.as<const char *>());
        if (ok) ledsStateUpdated();
        return ok;
    }
);

bool setSpeed(float value) {
    if (speed <= 0) {
        return false;
    }
    speed = value;
    return true;
}

bool setIntensity(float value) {
    if (value <= 0) {
        return false;
    }
    intensity = value;
    return true;
}

int registerAnimation(Animation *animation) {
    animations.push_back(animation);
    return animations.size() - 1;
}

int lookupAnimation(const char *name, size_t len) {
    for (unsigned int idx = 0; idx < animations.size(); idx++) {
        if (!strncmp(name, animations[idx]->name, len)) {
            return idx;
        }
    }
    return -1;
}

bool setAnimation(int idx) {
    if (idx < 0 || idx >= (int)animations.size()) {
        return false;
    }

    if (idx == animationIdx && animation != nullAnimation) {
        return true;
    }

    // TODO: consider transitions, like fade?
    if (started) animation->stop();
    animationIdx = idx;
    animation = animations[idx];
    if (started) animation->start();

    return true;
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
