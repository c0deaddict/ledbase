#pragma once

#include "config.h"
#include "leds.h"

extern float intensity;
extern RgbColor color;

class Animation {
private:
    unsigned long lastDraw;
    unsigned long lastTick;

    float intensityScalar = 1.0;

protected:
    int fps;

    void setIntensityScalar(float value) {
        intensityScalar = value;
    }

public:
    const char *name;

    Animation(const char *name) : Animation(name, FPS) {};

    Animation(const char *name, int fps)
        : lastDraw(0), lastTick(0), fps(fps), name(name) {};


    virtual void start() {};
    virtual void stop() {};
    virtual void draw() {};
    virtual void tick() {};
    virtual void beat() {};

    void update() {
        // Call tick() `intensity` times per second.
        if (intensity > 0 && millis() - lastTick > 1000.0f / (intensity * intensityScalar)) {
            lastTick = millis();
            tick();
        }

        // Call draw FPS times per second.
        if (millis() - lastDraw > 1000.0 / fps) {
            lastDraw = millis();
            draw();
            leds->show();
        }
    }
};

extern Animation *animation;
extern Animation *animationsList[];

int registerAnimation(Animation *animation);
bool isValidAnimation(int idx);
int lookupAnimation(const char *name, size_t len);
void setAnimation(int idx);
void startAnimation();
void stopAnimation();
