#include <espbase.h>
#include "animation.h"
#include "mode.h"

#define LEDS_TOPIC HASS_TOPIC("light", "leds")

extern int modeIdx;
extern int animationIdx;

Device ledsDevice(LEDS_TOPIC "/config", [](JsonObject &cfg) {
    cfg["~"] = LEDS_TOPIC;
    cfg["name"] = HOSTNAME;
    cfg["unique_id"] = HOSTNAME "_leds";
    cfg["command_topic"] = "~/set";
    cfg["state_topic"] = "~/state";
    cfg["schema"] = "json";
    cfg["brightness"] = true;
    cfg["effect"] = true;
    cfg["color_mode"] = true;

    JsonArray colorModes = cfg.createNestedArray("supported_color_modes");
    colorModes.add("rgb");

    JsonArray effectList = cfg.createNestedArray("effect_list");
    for (Animation *animation : animations) {
        effectList.add(animation->name);
    }
});

void ledsStateUpdated() {
    DynamicJsonDocument doc(1024);
    JsonObject state = doc.to<JsonObject>();

    state["brightness"] = leds->getBrightness();
    state["color_mode"] = "rgb";
    JsonObject colorState = state.createNestedObject("color");
    colorState["r"] = color.R;
    colorState["g"] = color.G;
    colorState["b"] = color.B;
    state["effect"] = animations[animationIdx]->name;
    state["state"] = modeIdx != 0 ? "ON" : "OFF";

    String buf;
    size_t len = serializeJson(doc, buf);
    mqtt.publish(LEDS_TOPIC "/state", 0, true, buf.c_str(), len);
}

MqttSub ledsCommandHandler(
    LEDS_TOPIC "/set", false,
    [](const char *topic, const char *payload, size_t len) {
        StaticJsonDocument<512> doc;
        DeserializationError err = deserializeJson(doc, payload, len);
        if (err) {
            logger->print("ledsCommandHandler: deserializeJson() failed: ");
            logger->println(err.c_str());
            return;
        }

        if (doc.containsKey("state")) {
            int newMode = !strcmp(doc["state"], "ON") ? 1 : 0;
            setMode(newMode);
        }

        if (doc.containsKey("brightness")) {
            leds->setBrightness(constrain(doc["brightness"].as<int>(), 0, 255));
        }

        if (doc.containsKey("color")) {
            byte r = doc["color"]["r"].as<byte>();
            byte g = doc["color"]["g"].as<byte>();
            byte b = doc["color"]["b"].as<byte>();
            color = RgbColor(r, g, b);
        }

        if (doc.containsKey("effect")) {
            const char *effect = doc["effect"];
            int newAnimation = lookupAnimation(effect, strlen(effect));
            if (newAnimation >= 0) {
                setAnimation(newAnimation);
            }
        }

        ledsStateUpdated();
    }
);
