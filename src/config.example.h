#pragma once

#define HOSTNAME "ledbase"

#define WIFI_SSID "Pretty Fly for a WiFi"
#define WIFI_PASSWORD "password123"

#define OTA_PASSWORD "password123"

// This is optional.
#define MQTT_HOST IPAddress(127, 0, 0, 1)
#define MQTT_PORT 1883
#define MQTT_USER "ledbase"
#define MQTT_PASSWORD "password123"

// Optional.
#define USE_NTP

#define UDP_PORT 1337
#define UDP_MAX_PACKET_SIZE 1460  // MTU 1500

#define LED_DEBUG

// For ESP32
#define LED_SHOW_CORE 1

#define LED_DEFAULT_BRIGHTNESS 255

#define DEFAULT_MOTION_DURATION 20

#define UDP_DEFAULT_TIMEOUT 60

#define MAX_MODES 10
#define MAX_ANIMATIONS 10

#define LED_COUNT 256
