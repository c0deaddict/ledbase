#include <espbase.h>
#include "config.h"
#include "mode.h"

#include "off_mode.h"
#include "on_mode.h"
#include "motion_mode.h"
#include "udp_mode.h"

Mode* modesList[MAX_MODES] = {
    new OffMode(),
    new OnMode(),
    new MotionMode(),
    new UdpMode(),
    NULL,
};

Mode *mode = modesList[0];

Setting modeSetting(
    "mode",
    [](JsonVariant& value) {
        value.set(0);
    },
    [](JsonVariant value) {
        int modeIdx = value.as<int>();
        if (!isValidMode(modeIdx)) return false;
        setMode(modeIdx);
        return true;
    }
);

int registerMode(Mode *mode) {
    for (int idx = 0; idx < MAX_MODES; idx++) {
        if (modesList[idx] == NULL) {
            modesList[idx] = mode;
            return idx;
        }
    }

    return -1;
}

bool isValidMode(int idx) {
    if (idx < 0 || idx >= MAX_MODES) {
        return false;
    }
    return modesList[idx] != NULL;
}

int lookupMode(const char *name, size_t len) {
    for (int idx = 0; idx < MAX_MODES; idx++) {
        Mode *mode = modesList[idx];
        if (mode != NULL) {
            if (!strncmp(name, mode->name, len)) {
                return idx;
            }
        }
    }
    return -1;
}

void setMode(int idx) {
    if (!isValidMode(idx)) return;

    Serial.printf("Changing mode to %d\n\r", idx);

    mode->leave();
    mode = modesList[idx];
    mode->enter();
}
