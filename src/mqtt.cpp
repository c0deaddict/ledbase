#include <espbase.h>
#include "animation.h"
#include "mode.h"

inline void copyAndTerminate(char *buf, size_t buflen, const char *src, size_t srclen) {
    strncpy(buf, src, min(buflen - 1, srclen));
    buf[buflen - 1] = 0;
}

void mqttControlHandler(const char *topic, const char *payload, size_t len) {
    const char *p = strrchr(topic, '/');
    if (p == NULL) return;
    p++; // Skip the slash

    if (!strcmp(p, "settings")) {
        Setting::patch((const char *)payload, len);
    } else if (!strcmp(p, "mode")) {
        int idx = lookupMode(payload, len);
        if (idx >= 0) setMode(idx);
    } else if (!strcmp(p, "animation")) {
        int idx = lookupAnimation(payload, len);
        if (idx >= 0) setAnimation(idx);
    } else if (!strcmp(p, "color")) {
        char buf[7];
        copyAndTerminate(buf, sizeof(buf), payload, len);
        setColor(buf);
    } else if (!strcmp(p, "speed")) {
        char buf[20];
        copyAndTerminate(buf, sizeof(buf), payload, len);
        setSpeed(atof(buf));
    } else if (!strcmp(p, "intensity")) {
        char buf[20];
        copyAndTerminate(buf, sizeof(buf), payload, len);
        setIntensity(atof(buf));
    } else {
        logger->printf("MQTT: unknown LEDs control message: %s\n\r", p);
    }
}

MqttSub mqttControlAll("leds/all/+", mqttControlHandler);
MqttSub mqttControlHost("leds/" HOSTNAME "/+", mqttControlHandler);

// Without this --gc-sections will strip this entire object file.
void mqttPreventGcSections() {
}
