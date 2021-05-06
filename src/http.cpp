#include "ledbase.h"

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

void setupHttp() {
    http.on("/motion", HTTP_POST, handlePostMotion);
    http.on("/names", HTTP_GET, handleGetNames); 
}
