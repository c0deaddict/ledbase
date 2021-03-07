#include "config.h"
#include "leds.h"
#include "settings.h"

CRGB leds[LED_COUNT];

// Task handles for use in the notifications
static TaskHandle_t showLedsTaskHandle = 0;
static TaskHandle_t userTaskHandle = 0;

/**
 * Call this function instead of FastLED.show(). It signals core 1 to issue a
 * show, then waits for a notification that it is done.
 */
bool showLeds() {
    if (userTaskHandle != 0) return false;

    // Store the handle of the current task, so that the show task can
    // notify it when it's done.
    userTaskHandle = xTaskGetCurrentTaskHandle();

    // Trigger the show task.
    xTaskNotifyGive(showLedsTaskHandle);

    // Wait to be notified that it's done.
    const TickType_t xMaxBlockTime = pdMS_TO_TICKS(50);
    ulTaskNotifyTake(pdTRUE, xMaxBlockTime);
    userTaskHandle = 0;

    return true;
}

bool ensureShowLeds() {
    if (showLeds()) return true;

    for (int i = 0; i < 11; i++) {
        vTaskDelay(pdMS_TO_TICKS(5));
        if (showLeds()) return true;
    }

    return false;
}

/**
 * This function runs on core 1 and just waits for requests to call
 * FastLED.show()
 */
void showLedsTask(void *pvParameters) {
    for(;;) {
        // Wait for the trigger.
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Do the show (synchronously)
        FastLED.show();

        // Notify the calling task.
        xTaskNotifyGive(userTaskHandle);
    }
}

void fillColor(CRGB color) {
    fill_solid(leds, LED_COUNT, color);
}

void clearLeds() {
    fillColor(CRGB::Black);
}

void ledsOff() {
    clearLeds();
    ensureShowLeds();
}

void setupLeds() {
    configureLeds();

    xTaskCreatePinnedToCore(showLedsTask, "showLedsTask", 2048, NULL, 2, &showLedsTaskHandle, LED_SHOW_CORE);

    FastLED.setBrightness(LED_DEFAULT_BRIGHTNESS);
    ledsOff();
}

void setBrightness(byte value) {
    FastLED.setBrightness(value);
}

Setting brightnessSetting(
    "brightness",
    [](JsonVariant& value) {
        value.set(LED_DEFAULT_BRIGHTNESS);
    },
    [](JsonVariant value) {
        int brightness = constrain(value.as<int>(), 0, 255);
        setBrightness(brightness);
        return true;
    }
);
