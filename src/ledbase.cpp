#include <espbase.h>
#include "ledbase.h"

void setupUdp();
void setupHttpRoutes();
void handleUdp();
void mqttPreventGcSections();

void setupLedbase() {
    // LEDs need to be setup before network.
    leds->setup();
    mode->enter();

    // Setup http routes before calling setupEspbase.
    setupHttpRoutes();
    mqttPreventGcSections();
    setupEspbase();
    setupUdp();
}

void handleLedbase() {
    handleEspbase();
    handleUdp();

    mode->update();
}
