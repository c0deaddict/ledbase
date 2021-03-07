#include "ledbase.h"

void setupNetwork();
void setupOta();
void setupLeds();
void setupUdp();
void setupHttp();
void handleOta();
void handleUdp();
void loadSettings();

void setupLedbase() {
    Serial.begin(115200);

    setupNetwork();
    setupOta();

    delay(3000);

    setupLeds();
    mode->enter();

    setupUdp();
    setupHttp();
    loadSettings();
}

void handleLedbase() {
    handleOta();
    handleUdp();

    mode->update();
}
