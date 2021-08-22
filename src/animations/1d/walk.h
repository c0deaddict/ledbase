#pragma once

#include <animation.h>

class Walk : public Animation {
private:
    float offset;
    
public:
    Walk();
    void draw();
};
