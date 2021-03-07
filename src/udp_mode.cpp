#include "config.h"
#include "udp_mode.h"
#include "leds.h"

UdpMode::UdpMode()
    : Mode("udp")
    , active(false)
    , lastFrameTime(0)
    , timeout(UDP_DEFAULT_TIMEOUT) {
    timeoutSetting = new Setting(
        "udpTimeout",
        [](JsonVariant& value) {
            value.set(UDP_DEFAULT_TIMEOUT);
        },
        [this](JsonVariant value) {
            int newTimeout = value.as<int>();
            // 0 = special: disable timeout
            if (newTimeout < 0) return false;
            timeout = newTimeout;
            return true;
        }
    );
}

void UdpMode::enter() {
    ledsOff();

    active = false;
    lastFrameTime = 0;
}

void UdpMode::update() {
    // If no data has been received for `timeout` seconds, turn off the leds.
    if (timeout != 0) {
        if (active && millis() - lastFrameTime >= timeout * 1000L) {
            ledsOff();
            active = false;
        }
    }
}

#define FLAG_SYNC 1
#define FLAG_RAW 2

void UdpMode::onData(byte *data, size_t len) {
    // Even invalid frames count as data received.
    lastFrameTime = millis();
    active = true;

    if (len <= 5) return;

    byte flags = data[0];
    int offset = (data[1] << 8) | data[2];
    int count = (data[3] << 8) | data[4];

    if (len - 5 > count * 3) {
        Serial.println("Udp packet contains invalid count");
        return;
    }

    for (int i = offset, j = 5; i < offset + count; i++, j += 3) {
        CRGB color = CRGB(data[j], data[j + 1], data[j + 2]);

        if (flags & FLAG_RAW) {
            if (i < LED_COUNT) {
                leds[i] = color;
            }
        } else {
            setLogicalPixel(i, color);
        }
    }

    if (flags & FLAG_SYNC) {
        showLeds();
    }
}
