#include "espbase.h"
#include "animation.h"
#include "mode.h"

void mqttControlMessage(char *topic, char *payload, size_t len) {
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
        char color[7];
        strncpy(color, payload, min(len, (size_t)6));
        color[6] = 0;
        setColor(color);
    } else {
        Serial.printf("Unknown MQTT control message: %s\n\r", topic);
    }
}
