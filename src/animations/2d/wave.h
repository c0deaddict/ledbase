#pragma once

#include <animation.h>

class Wave : public Animation {
public:
    Wave() : Animation("wave", 60) {};
    void tick();
};
