#include "display.h"
#include <U8g2lib.h>

static U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

static const uint8_t PAGE_COUNT = 3;

static void drawHeart() {
  u8g2.drawDisc(52, 28, 12);
  u8g2.drawDisc(76, 28, 12);
  u8g2.drawTriangle(41, 34, 87, 34, 64, 58);
}

static void drawFlower() {
  const int8_t offsets[6][2] = {{12, 0}, {-12, 0}, {6, -10},
                                {-6, -10}, {6, 10}, {-6, 10}};
  for (uint8_t i = 0; i < 6; i++) {
    u8g2.drawCircle(64 + offsets[i][0], 28 + offsets[i][1], 7);
  }
  u8g2.drawDisc(64, 28, 5);
  u8g2.drawLine(64, 45, 64, 63);                // stem
  u8g2.drawTriangle(64, 56, 76, 50, 70, 60);    // leaf
}

static void drawMessage() {
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(8, 28, "Chuc mung 20/10");       // edit your message here
  u8g2.drawStr(8, 50, "Anh yeu em!");
}

void displayBegin() {
  u8g2.begin();
  displayClear();
  displayOff();
}

void displayClear() {
  u8g2.clearBuffer();
  u8g2.sendBuffer();
}

void displayText(const char* line1, const char* line2) {
  u8g2.setPowerSave(0);
  u8g2.setFont(u8g2_font_6x12_tf);
  u8g2.clearBuffer();
  u8g2.drawStr(0, 20, line1);
  u8g2.drawStr(0, 40, line2);
  u8g2.sendBuffer();
}

void displayOff() { u8g2.setPowerSave(1); }

uint8_t displayPageCount() { return PAGE_COUNT; }

void displayShowPage(uint8_t page) {
  u8g2.setPowerSave(0);
  u8g2.clearBuffer();
  switch (page) {
    case 0:  drawHeart();   break;
    case 1:  drawFlower();  break;
    default: drawMessage(); break;
  }
  u8g2.sendBuffer();
}