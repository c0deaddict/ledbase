#include <espbase.h>
#include "config.h"
#include "udp_mode.h"
#include "leds.h"

#define FRAME_SYNC 1
#define FRAME_RAW 2

UdpMode::UdpMode()
    : Mode("udp")
    , active(false)
    , lastFrameTime(0)
    , timeout(UDP_DEFAULT_TIMEOUT)
    , beatDuration(0) {
    timeoutSetting = new Setting(
        "udpTimeout",
        [this](JsonDocument &doc, const char *name) {
            doc[name] = timeout;
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
    leds->off();

    active = false;
    lastFrameTime = 0;
}

void UdpMode::update() {
    // If no data has been received for `timeout` seconds, turn off the leds.
    if (timeout != 0) {
        if (active && millis() - lastFrameTime >= timeout * 1000L) {
            leds->off();
            active = false;
        }
    }

    if (beatDuration != 0) {
        if (millis() - beatStart >= beatDuration) {
            // Stop the beat.
            beatDuration = 0;
            leds->off();
        }
    }
}

void UdpMode::onFrame(byte *data, size_t len) {
    if (len < 6) return;

    beatDuration = 0;
    lastFrameTime = millis();
    active = true;

    byte flags = data[1];
    int offset = (data[2] << 8) | data[3];
    int count = (data[4] << 8) | data[5];

    if (len - 6 > (size_t)count * 3) {
        Serial.println("Udp frame contains invalid count");
        return;
    }

    for (int i = offset, j = 6; i < offset + count; i++, j += 3) {
        RgbColor color(data[j], data[j + 1], data[j + 2]);

        if (flags & FRAME_RAW) {
            if (i < LED_COUNT) {
                leds->setRawPixel(i, color);
            }
        } else {
            leds->setPixel(i, color);
        }
    }

    if (flags & FRAME_SYNC) {
        leds->show();
    }
}

bool UdpMode::onBeat(byte *data, size_t len) {
    if (len < 5) return true;

    active = false;

    beatDuration = 10 * (unsigned int)data[1]; // 1 = 10ms
    beatColor = RgbColor(data[2], data[3], data[4]);
    beatStart = millis();

    leds->fill(beatColor);
    leds->show();

    return true;
}
