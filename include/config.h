#pragma once
#include <Arduino.h>

// Servo signal pin (NodeMCU label D5)
constexpr uint8_t PIN_SERVO = D5;

// Servo angles, tune after mounting the latch
constexpr int ANGLE_LOCKED = 0;
constexpr int ANGLE_OPEN = 90;

// OLED uses the default I2C pins: SDA = D2, SCL = D1

constexpr uint8_t PIN_PAGE_BUTTON = D7;  // push button to GND
constexpr uint8_t PIN_LID_SWITCH  = D0;  // micro switch (NO) to 3V3
constexpr uint8_t PIN_CARD_SIM    = D3;  // NodeMCU FLASH button, fake card tap

// Set to true once the lid micro switch is installed
constexpr bool USE_LID_SWITCH = false;