#if LED_DIM == 2
#include "life.h"

// Determines the size of the field. For example for N=3 the virtual field for a
// 15x15 LED screen becomes 45x45.
#define N 3

#define WIDTH LED_XLEN*N
#define HEIGHT LED_YLEN*N
#define CELL_COUNT WIDTH*HEIGHT
#define CELL_IDX(x, y) ((y) * WIDTH + (x))
#define OFFSET_X (WIDTH - LED_XLEN + 1)/2
#define OFFSET_Y (HEIGHT - LED_YLEN + 1)/2

const CRGB DEAD = CRGB(0, 0, 0);

const int neighbourOffsets[8] = {
    CELL_IDX(-1, -1), // y-1, x-1
    CELL_IDX(-1, 0),  // y-1, x
    CELL_IDX(-1, +1), // y-1, x+1
    CELL_IDX(0, -1),  // x-1
    // x, y
    CELL_IDX(0, +1),  // x+1
    CELL_IDX(+1, -1), // y+1, x-1
    CELL_IDX(+1, 0),  // y+1, x
    CELL_IDX(+1, +1), // y+1, x+1
};

void Life::start() {
    cells1 = (CRGB *)malloc(sizeof(CRGB) * CELL_COUNT);
    cells2 = (CRGB *)malloc(sizeof(CRGB) * CELL_COUNT);
    currentGen = cells1;
    nextGen = cells2;

    if (cells1 != NULL && cells2 != NULL) {
        seed();
    }
}

void Life::stop() {
    if (cells1 != NULL) free(cells1);
    if (cells2 != NULL) free(cells2);
}

// Place seed.
void Life::seed() {
    Serial.println("life reseeding");

    gen = 0;

    for (int i = 0; i < CELL_COUNT; i++) {
        currentGen[i] = DEAD;
    }

    int num = random(6, 18);
    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
            if (random(0, 25) <= num) {
                int idx = CELL_IDX(WIDTH/2 + x, HEIGHT/2 + y);
                currentGen[idx] = CHSV(random(0, 256), 255, 255);
            }
        }
    }
}

int Life::countNeighbours(int idx, CRGB *avgColor) {
    int count = 0, r = 0, g = 0, b = 0;
    for (int i = 0; i < 8; i++) {
        int j = idx + neighbourOffsets[i];
        if (j >= 0 && j < CELL_COUNT) {
            CRGB color = currentGen[j];
            if (color != DEAD) {
                count++;
                r += color.r;
                g += color.g;
                b += color.b;
            }
        }
    }
    if (count > 0) {
        r /= count;
        g /= count;
        b /= count;
    }
    *avgColor = CRGB(r, g, b);
    return count;
}

bool Life::computeNextGen() {
    int changes = 0;

    // Compute the next generation.
    for (int i = 0; i < CELL_COUNT; i++) {
        CRGB avgColor;
        int count = countNeighbours(i, &avgColor);
        if (currentGen[i] == DEAD) {
            if (count == 3) {
                // Dead cell becomes alive.
                nextGen[i] = avgColor;
                changes++;
            } else {
                nextGen[i] = DEAD;
            }
        } else {
            if (count != 2 && count != 3) {
                // Life cell dies.
                nextGen[i] = DEAD;
                changes++;
            } else {
                nextGen[i] = currentGen[i];
            }
        }
    }

    std::swap(currentGen, nextGen);
    gen++;

    return changes > 0;
}

void Life::tick() {
    // Could be NULL if there is not enough RAM.
    if (cells1 == NULL || cells2 == NULL) return;

    bool changed = computeNextGen();

    // Start anew if nothing changed.
    if (!changed) {
        seed();
    }

    // Draw the visible part of the field.
    bool anyLife = false;
    for (int x = 0; x < LED_XLEN; x++) {
        for (int y = 0; y < LED_YLEN; y++) {
            int idx = CELL_IDX(x + OFFSET_X, y + OFFSET_Y);
            CRGB color = currentGen[idx];
            setPixel(x, y, color);
            anyLife |= color != DEAD;
        }
    }

    // Start anew if no life is on display, or we are at gen 200.
    if (!anyLife || gen > 200) {
        seed();
    }
}
#endif
