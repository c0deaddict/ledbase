#pragma once

#include "config.h"
#include "leds.h"

extern float intensity;
extern float speed;
extern RgbColor color;

class Animation {
private:
    unsigned long lastDraw;

protected:
    int fps;

public:
    const char *name;

    Animation(const char *name) : Animation(name, FPS) {};

    Animation(const char *name, int fps)
        : lastDraw(0), fps(fps), name(name) {};


    virtual void start() {};
    virtual void stop() {};
    virtual void draw() {};
    virtual void beat() {};

    void update() {
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
bool setColor(const char *str);
bool setSpeed(float value);
bool setIntensity(float value);
void startAnimation();
void stopAnimation();
