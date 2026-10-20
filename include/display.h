#pragma once
#include <Arduino.h>

void displayBegin();
void displayClear();
void displayText(const char* line1, const char* line2);
void displayOff();
uint8_t displayPageCount();
void displayShowPage(uint8_t page, uint16_t frame);