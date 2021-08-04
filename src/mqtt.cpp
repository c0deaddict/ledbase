#include <espbase.h>
#include "animation.h"
#include "mode.h"

inline void copyAndTerminate(char *buf, size_t buflen, const char *src, size_t srclen) {
    strncpy(buf, src, min(buflen - 1, srclen));
    buf[buflen - 1] = 0;
}

MqttSub mqttLedMode(
    "leds/mode/+", true,
    [](const char *topic, const char *payload, size_t len) {
        int idx = lookupMode(payload, len);
        if (idx >= 0) setMode(idx);
    }
);

MqttSub mqttLedAnimation(
    "leds/animation/+", true,
    [](const char *topic, const char *payload, size_t len) {
        int idx = lookupAnimation(payload, len);
        if (idx >= 0) setAnimation(idx);
    }
);

MqttSub mqttLedColor(
    "leds/color/+", true,
    [](const char *topic, const char *payload, size_t len) {
        char buf[7];
        copyAndTerminate(buf, sizeof(buf), payload, len);
        setColor(buf);
    }
);

// Without this --gc-sections will strip this entire object file.
void mqttPreventGcSections() {
}
