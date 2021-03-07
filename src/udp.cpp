#include <Arduino.h>
#include <WiFiUdp.h>

#include "config.h"
#include "mode.h"
#include "network.h"

WiFiUDP udpSocket;
byte packetBuffer[UDP_MAX_PACKET_SIZE];

void setupUdp() {
    udpSocket.begin(UDP_PORT);
}

void handleUdp() {
    int packetSize = udpSocket.parsePacket();
    if (packetSize) {
        int len = udpSocket.read(packetBuffer, sizeof(packetBuffer));
        if (len > 0) {
            mode->onData(packetBuffer, len);
        }
    }
}
