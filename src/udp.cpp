#include <espbase.h>
#include "config.h"
#include "mode.h"
#include "animation.h"

WiFiUDP udpSocket;
byte packetBuffer[UDP_MAX_PACKET_SIZE];

void setupUdp() {
    udpSocket.begin(UDP_PORT);
}

#define TYPE_FRAME 0
#define TYPE_BEAT 1

void handleUdp() {
    int packetSize = udpSocket.parsePacket();
    if (packetSize) {
        int len = udpSocket.read(packetBuffer, sizeof(packetBuffer));
        if (len > 0) {
            byte type = packetBuffer[0];
            switch (type) {
            case TYPE_FRAME:
                mode->onFrame(packetBuffer, len);
                break;

            case TYPE_BEAT:
                if (!mode->onBeat(packetBuffer, len)) {
                    animation->beat();
                }
                break;
            }
        }
    }
}
