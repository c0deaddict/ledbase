#include "ledbase.h"
#include <AsyncJson.h>

AsyncWebServer http(80);

void handleGetMetrics(AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("text/plain");
    printMetrics(response);
    request->send(response);
}

void handlePostControl(AsyncWebServerRequest *request) {
    int numParams = request->params();
    for (int i = 0; i < numParams; i++) {
        AsyncWebParameter *p = request->getParam(i);
        if (!p->isFile()) { // accept GET or POST parameters
            DynamicJsonDocument doc(256);
            DeserializationError err = deserializeJson(doc, p->value());
            if (err) {
                Serial.print(F("handlePostControl: deserializeJson() failed: "));
                Serial.println(err.c_str());
            }
            else if (setSetting(p->name().c_str(), doc.as<JsonVariant>())) {
                saveSettings();
            }
        }
    }

    request->send(200, "application/json", getSettingsAsJson());
}

void handleGetSettings(AsyncWebServerRequest *request) {
    request->send(200, "application/json", getSettingsAsJson());
}

void handlePostSettings(AsyncWebServerRequest *request, JsonVariant &json) {
    bool save = false;
    for (auto kvp : json.as<JsonObject>()) {
        save |= setSetting(kvp.key().c_str(), kvp.value());
    }
    if (save) {
        saveSettings();
    }
    request->send(200, "application/json", getSettingsAsJson());
}

void handlePostMotion(AsyncWebServerRequest *request) {
    mode->onMotionChange(true);
    request->send(200, "text/plain", "Ok");
}

void handleGetNames(AsyncWebServerRequest *request) {
    AsyncJsonResponse * response = new AsyncJsonResponse();
    JsonObject root = response->getRoot();

    JsonArray modesJson = root.createNestedArray("modes");
    for (int i = 0; i < MAX_MODES && modesList[i] != NULL; i++) {
        modesJson.add(modesList[i]->name);
    }

    JsonArray animationsJson = root.createNestedArray("animations");
    for (int i = 0; i < MAX_ANIMATIONS && animationsList[i] != NULL; i++) {
        animationsJson.add(animationsList[i]->name);
    }

    response->setLength();
    request->send(response);
}

void handleRestart(AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Ok");
    vTaskDelay(pdMS_TO_TICKS(100));
    ESP.restart();
}

void setupHttp() {
    http.on("/metrics", HTTP_GET, handleGetMetrics);
    http.on("/control", HTTP_POST, handlePostControl);
    http.on("/settings", HTTP_GET, handleGetSettings);
    http.on("/motion", HTTP_POST, handlePostMotion);
    http.on("/names", HTTP_GET, handleGetNames);
    http.on("/restart", HTTP_POST, handleRestart);

    AsyncCallbackJsonWebHandler* postSettings =
        new AsyncCallbackJsonWebHandler("/settings", handlePostSettings);
    postSettings->setMethod(HTTP_POST);
    http.addHandler(postSettings);

    http.onNotFound([](AsyncWebServerRequest *request){
        request->send(404, "text/plain", "Not Found");
    });
 
    http.begin();
}
