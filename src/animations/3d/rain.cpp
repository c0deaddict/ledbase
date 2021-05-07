#if LED_DIM == 3
#include "rain.h"

#define DROP_TAIL 3

void Rain::start() {
    clearLeds();

    for (int i = 0; i < MAX_DROPS; i++) {
        drops[i] = {x: -1, y: -1, z: -1};
    }
}

void Rain::newDrop() {
    // Find a free drop slot.
    int i = 0;
    for (i = 0; i < MAX_DROPS; i++) {
        if (drops[i].y < 0) {
            break;
        }
    }

    if (i == MAX_DROPS) {
        return;
    }

    // 3 tries to find a unique (x, z)
    for (int k = 0; k < 3; k++) {
        drops[i].x = random(0, LED_XLEN);
        drops[i].z = random(0, LED_ZLEN);

        for (int j = 0; j < MAX_DROPS; j++) {
            if (drops[j].y >= 0) {
                if (drops[i].x == drops[j].x && drops[i].z == drops[j].z) {
                    goto retry;
                }
            }
        }

        drops[i].y = LED_YLEN + DROP_TAIL;
        return;

    retry:;
    }
}

void Rain::tick() {
    if (random(0, 3) == 0) {
        newDrop();
    }

    for (Drop *d = drops; d < drops + MAX_DROPS; d++) {
        if (d->y >= 0) {
            setPixel(d->x, d->y, d->z, CRGB::Black);
            d->y -= 1;

            for (int j = 0; j < DROP_TAIL; j++) {
                byte c = 32 + ((255 - 32)/(DROP_TAIL - 1)) * j;
                setPixel(d->x, d->y - j, d->z, CHSV(hue, 255, c));
            }
        }
    }
}

void Rain::beat() {
    hue += 66;
}
#endif
