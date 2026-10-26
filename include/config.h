#pragma once
#include <Arduino.h>

// Servo
constexpr uint8_t PIN_SERVO   = D4;
constexpr int ANGLE_LOCKED    = 0;
constexpr int ANGLE_OPEN      = 90;

// OLED uses default I2C: SDA = D2, SCL = D1

// Micro switch (COM→GND, NO→pin)
constexpr uint8_t PIN_LID_SWITCH = D5;
constexpr bool    USE_LID_SWITCH = true;   // đổi true khi đã hàn dây xong

// RDM6300
constexpr uint8_t PIN_RDM_RX = D7;
constexpr uint8_t PIN_RDM_TX = D8;   // không dùng, chỉ cần khai báo

// ID thẻ thang máy — thay bằng ID đọc được lúc test
const String CARD_ID = "15006ED28F";

// Timing
constexpr unsigned long FRAME_MS = 150;
constexpr unsigned long PAGE_MS  = 3500;