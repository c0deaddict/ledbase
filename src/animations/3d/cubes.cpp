#if LED_DIM == 3
#include "cubes.h"

#define BOX_LEN 3
#define MOVE (LED_XLEN - BOX_LEN)

Cubes::Cubes() : Animation("cubes") {
}

void Cubes::start() {
    t = 0;
}

void Cubes::fillBox(int x1, int y1, int z1, int x2, int y2, int z2, CRGB color) {
    for (int x = x1; x < x2; x++) {
        for (int y = y1; y < y2; y++) {
            for (int z = z1; z < z2; z++) {
                setPixel(x, y, z, color);
            }
        }
    }
}

void Cubes::drawCube(int offset, int y1, CRGB color) {
    int j = t % MOVE;
    int y2 = y1 + BOX_LEN;

    switch ((offset + (t / MOVE)) % 4) {
    case 0:
        // move in +z
        fillBox(0, y1, j, BOX_LEN, y2, j + BOX_LEN, color);
        break;

    case 1:
        // move in +x
        fillBox(j, y1, MOVE, j + BOX_LEN, y2, LED_ZLEN, color);
        break;

    case 2:
        // move in -z
        fillBox(MOVE, y1, LED_ZLEN - j - BOX_LEN, LED_XLEN, y2, LED_ZLEN - j, color);
        break;

    case 3:
        // move in -x
        fillBox(LED_XLEN - j - BOX_LEN, y1, 0, LED_XLEN - j, y2, BOX_LEN, color);
        break;
    }
}

void Cubes::tick() {
    fillColor(CRGB::Black);

    t = (t + 1) % (4 * MOVE);

    drawCube(0, 0, CRGB(255, 0, 0));
    drawCube(1, MOVE, CRGB(255, 255, 0));
    drawCube(2, 0, CRGB(0, 255, 0));
    drawCube(3, MOVE, CRGB(0, 0, 255));
}
#endif
