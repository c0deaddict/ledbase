#include <espbase.h>
#include "ledbase.h"

void setupLeds();
void setupUdp();
void setupHttp();
void handleUdp();

void setupLedbase() {
    // LEDs need to be setup before network.
    delay(3000);
    setupLeds();
    mode->enter();

    // Setup http routes before calling setupEspbase.
    setupHttp();
    setupEspbase();
    setupUdp();
}

void handleLedbase() {
    handleEspbase();
    handleUdp();

    mode->update();
}
