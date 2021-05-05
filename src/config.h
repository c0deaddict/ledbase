#pragma once

// Required

#ifndef HOSTNAME
#error "HOSTNAME is not configured"
#endif

#ifndef MQTT_HOST
#error "MQTT_HOST is not configured"
// Example:
// #define MQTT_HOST IPAddress(10, 13, 37, 4)
#endif

#ifndef WIFI_SSID
#error "WIFI_SSID is not configured"
#endif

#ifndef WIFI_PASSWORD
#error "WIFI_PASSWORD is not configured"
#endif

#ifndef OTA_PASSWORD
#error "OTA_PASSWORD is not configured"
#endif

#ifndef MQTT_USER
#error "MQTT_USER is not configured"
#endif

#ifndef MQTT_PASSWORD
#error "MQTT_PASSWORD is not configured"
#endif

#ifndef LED_COUNT
#error "LED_COUNT is not configured"
#endif

#ifndef LED_DIM
#error "LED_DIM is not configured"
#endif

#if LED_DIM == 2 || LED_DIM == 3

#ifndef LED_XLEN
#error "LED_XLEN is not configured"
#endif
#ifndef LED_YLEN
#error "LED_YLEN is not configured"
#endif

#endif

#if LED_DIM == 3
#ifndef LED_ZLEN
#error "LED_ZLEN is not configured"
#endif
#endif

// Optional

#ifndef MQTT_PORT
#define MQTT_PORT 1883
#endif

#ifndef UDP_PORT
#define UDP_PORT 1337
#endif

#ifndef UDP_MAX_PACKET_SIZE
#define UDP_MAX_PACKET_SIZE 1460  // MTU 1500
#endif

#ifndef LED_SHOW_CORE
#define LED_SHOW_CORE 1
#endif

#ifndef LED_DEFAULT_BRIGHTNESS
#define LED_DEFAULT_BRIGHTNESS 255
#endif

#ifndef DEFAULT_MOTION_DURATION
#define DEFAULT_MOTION_DURATION 20
#endif

#ifndef UDP_DEFAULT_TIMEOUT
#define UDP_DEFAULT_TIMEOUT 60
#endif

#ifndef MAX_MODES
#define MAX_MODES 10
#endif

#ifndef MAX_ANIMATIONS
#define MAX_ANIMATIONS 10
#endif
