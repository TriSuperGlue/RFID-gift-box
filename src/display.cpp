#include "display.h"
#include <U8g2lib.h>

static U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void displayBegin() {
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x12_tf);
  displayClear();
}

void displayClear() {
  u8g2.clearBuffer();
  u8g2.sendBuffer();
}

void displayText(const char* line1, const char* line2) {
  u8g2.clearBuffer();
  u8g2.drawStr(0, 20, line1);
  u8g2.drawStr(0, 40, line2);
  u8g2.sendBuffer();
}