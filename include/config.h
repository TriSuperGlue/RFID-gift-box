#pragma once
#include <Arduino.h>

// Servo signal pin (NodeMCU label D5)
constexpr uint8_t PIN_SERVO = D4;

// Servo angles, tune after mounting the latch
constexpr int ANGLE_LOCKED = 0;
constexpr int ANGLE_OPEN = 90;

// OLED uses the default I2C pins: SDA = D2, SCL = D1

constexpr uint8_t PIN_LID_SWITCH  = D0;  // micro switch (NO) to 3V3
constexpr uint8_t PIN_CARD_SIM    = D3;  // NodeMCU FLASH button, fake card tap

// Set to true once the lid micro switch is installed
constexpr bool USE_LID_SWITCH = false;

constexpr unsigned long FRAME_MS = 150;   // animation frame interval
constexpr unsigned long PAGE_MS  = 3500;  // how long each page stays on screen