#pragma once
#include <Arduino.h>

// Servo signal pin (NodeMCU label D5)
constexpr uint8_t PIN_SERVO = D5;

// Servo angles, tune after mounting the latch
constexpr int ANGLE_LOCKED = 0;
constexpr int ANGLE_OPEN = 90;

// OLED uses the default I2C pins: SDA = D2, SCL = D1