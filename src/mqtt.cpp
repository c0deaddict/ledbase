#include "espbase.h"
#include "animation.h"
#include "mode.h"

void mqttControlMessage(char *topic, char *payload, size_t len) {
    const char *p = strrchr(topic, '/');
    if (p == NULL) return;
    p++; // Skip the slash

    if (!strcmp(p, "settings")) {
        if (mergeSettings((const char *)payload, len)) {
            saveSettings();
        }
    } else if (!strcmp(p, "mode")) {
        int idx = lookupMode(payload, len);
        if (idx >= 0) setMode(idx);
    } else if (!strcmp(p, "animation")) {
        int idx = lookupAnimation(payload, len);
        if (idx >= 0) setAnimation(idx);
    } else {
        Serial.printf("Unknown MQTT control message: %s\n\r", topic);
    }
}
