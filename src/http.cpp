#include "ledbase.h"
#include <AsyncJson.h>

void handlePostMotion(AsyncWebServerRequest *request) {
    mode->onMotionChange(true);
    request->send(200, "text/plain", "Ok");
}

void handleGetNames(AsyncWebServerRequest *request) {
    AsyncJsonResponse * response = new AsyncJsonResponse();
    JsonObject root = response->getRoot();

    JsonArray modesJson = root.createNestedArray("modes");
    for (Mode *mode : modes) {
        modesJson.add(mode->name);
    }

    JsonArray animationsJson = root.createNestedArray("animations");
    for (Animation *animation : animations) {
        animationsJson.add(animation->name);
    }

    JsonArray palettesJson = root.createNestedArray("palettes");
    for (Palette *palette : palettes) {
        palettesJson.add(palette->name);
    }

    response->setLength();
    request->send(response);
}

void setupHttpRoutes() {
    http.on("/motion", HTTP_POST, handlePostMotion);
    http.on("/names", HTTP_GET, handleGetNames); 
}
