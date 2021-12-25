#include <espbase.h>
#include "config.h"
#include "mode.h"

#include "off_mode.h"
#include "on_mode.h"
#include "motion_mode.h"
#include "udp_mode.h"

std::vector<Mode *> modes = {
    new OffMode(),
    new OnMode(),
    new MotionMode(),
    new UdpMode(),
};

int modeIdx = 0;
Mode *mode = modes[modeIdx];

void ledsStateUpdated();

Setting modeSetting(
    "mode",
    [](JsonObject &obj, const char *name) {
        obj[name] = modeIdx;
    },
    [](JsonVariant value) {
        int modeIdx = value.as<int>();
        bool ok = setMode(modeIdx);
        if (ok) ledsStateUpdated();
        return ok;
    }
);

int registerMode(Mode *mode) {
    modes.push_back(mode);
    return modes.size() - 1;
}

int lookupMode(const char *name, size_t len) {
    for (unsigned int idx = 0; idx < modes.size(); idx++) {
        if (!strncmp(name, modes[idx]->name, len)) {
            return idx;
        }
    }
    return -1;
}

bool setMode(int idx) {
    if (idx < 0 || idx >= (int)modes.size()) {
        return false;
    }

    if (idx == modeIdx) {
        return true;
    }

    Serial.printf("Changing mode to %d\n\r", idx);

    mode->leave();
    modeIdx = idx;
    mode = modes[idx];
    mode->enter();

    return true;
}
