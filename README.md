# Ledbase Arduino library

Base for my Platformio LED matrix projects running on a ESP32.

## Include

Include the library in `platformio.ini`:

```toml
[env]
lib_deps = https://github.com/c0deaddict/ledbase.git#master
```

## Config

Ledbase requires configuration preprocessor variables to be declared at build
time. This can be accomplished by adding your config to the `build_flags` in
`platformio.ini`.

```toml
build_flags = -include "src/config.h"
```

See ./src/config.example.h for an example configuration.

## Main

Initialize ledbase in `main.cpp`:

```c
#include <ledbase.h>

#include "animations/wave.h"
#include "animations/random.h"
#include "animations/life.h"

#include "fft_mode.h"

void prepareMqtt();

void setup() {
    Serial.begin(115200);

    registerAnimation(new Wave());
    registerAnimation(new Random());
    registerAnimation(new Life());

    registerMode(new FftMode());
    prepareMqtt();
    setupLedbase();
}

void loop() {
    handleLedbase();
}
```

## MQTT

If you want to subscribe to MQTT messages, you must do so before calling
`setupLedbase`:

```c
void mqttOnMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
    Serial.printf("Received mqtt message on %s: %.*s\n\r", topic, len, payload);
}

// Must be called before setupLedbase()
void prepareMqtt() {
    mqtt.onConnect([](bool sessionPresent) {
        Serial.println("Connected to MQTT!");
        mqtt.subscribe("sensors/+/pir", 0);
    });
    mqtt.onMessage(mqttOnMessage);
}
```
