#include "display.h"
#include <U8g2lib.h>

static U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

static const uint8_t PAGE_COUNT = 4;

// ---------- helpers ----------

static void drawCentered(int y, const char* text) {
  int x = (128 - u8g2.getStrWidth(text)) / 2;
  u8g2.drawStr(x, y, text);
}

static void drawSparkle(int x, int y, int s) {
  u8g2.drawLine(x - s, y, x + s, y);
  u8g2.drawLine(x, y - s, x, y + s);
}

static void drawHeartShape(int cx, int cy, int r) {
  u8g2.drawDisc(cx - r, cy, r);
  u8g2.drawDisc(cx + r, cy, r);
  u8g2.drawTriangle(cx - 2 * r + 1, cy + r / 3,
                    cx + 2 * r - 1, cy + r / 3,
                    cx, cy + (5 * r) / 2);
}

static void drawFlower(int cx, int cy, int pr, bool filled) {
  int d = (pr * 17) / 10;   // distance of the petals from the center
  int h = d / 2;
  int v = (d * 87) / 100;
  const int px[6] = {d, -d, h, -h, h, -h};
  const int py[6] = {0, 0, -v, -v, v, v};
  for (uint8_t i = 0; i < 6; i++) {
    if (filled) u8g2.drawDisc(cx + px[i], cy + py[i], pr);
    else        u8g2.drawCircle(cx + px[i], cy + py[i], pr);
  }
  if (filled) {
    u8g2.setDrawColor(0);
    u8g2.drawDisc(cx, cy, pr / 2 + 1);   // dark center
    u8g2.setDrawColor(1);
    u8g2.drawDisc(cx, cy, pr / 3);       // bright dot
  } else {
    u8g2.drawDisc(cx, cy, pr / 2 + 1);
  }
}

static void drawStem(int x, int top, int bottom, bool leafRight) {
  u8g2.drawVLine(x, top, bottom - top);
  int mid = top + (bottom - top) / 2;
  int dir = leafRight ? 1 : -1;
  u8g2.drawTriangle(x, mid, x + dir * 7, mid - 4, x + dir * 7, mid + 2);
}

// ---------- pages ----------

static void drawHeartPage(uint16_t frame) {
  uint8_t beat = frame % 8;
  int r = (beat == 0 || beat == 2) ? 14 : 12;   // two quick beats, then rest
  const int cx = 64;
  const int cy = 24;
  drawHeartShape(cx, cy, r);

  u8g2.setDrawColor(0);                          // small shine on the heart
  u8g2.drawCircle(cx - r - 3, cy - 3, 3, U8G2_DRAW_UPPER_LEFT);
  u8g2.setDrawColor(1);

  if ((frame / 2) % 2) {
    drawSparkle(14, 14, 3);
    drawSparkle(112, 20, 2);
    drawSparkle(104, 52, 3);
  } else {
    drawSparkle(18, 48, 2);
    drawSparkle(116, 10, 3);
    drawSparkle(10, 30, 2);
  }
}

static void drawGardenPage(uint16_t frame) {
  bool phase = (frame / 6) % 2;
  // stems first, flowers on top
  drawStem(26, 38, 62, true);
  drawStem(64, 36, 62, false);
  drawStem(102, 38, 62, true);
  drawStem(45, 52, 62, false);
  drawStem(84, 54, 62, true);

  drawFlower(26, 22, 6, !phase);
  drawFlower(64, 18, 7, phase);
  drawFlower(102, 22, 6, !phase);
  drawFlower(45, 44, 3, phase);
  drawFlower(84, 46, 3, !phase);

  u8g2.drawHLine(0, 63, 128);                    // ground
}

static void drawGreetingPage(uint16_t frame) {
  u8g2.setFont(u8g2_font_ncenB14_tr);
  drawCentered(24, "Happy");
  u8g2.setFont(u8g2_font_ncenB10_tr);
  drawCentered(44, "Women's Day");
  u8g2.setFont(u8g2_font_6x10_tf);
  drawCentered(60, "20 / 10");

  if ((frame / 3) % 2) {
    drawSparkle(10, 12, 3);
    drawSparkle(118, 12, 3);
  } else {
    drawSparkle(14, 50, 2);
    drawSparkle(114, 50, 2);
  }
}

static void drawLovePage(uint16_t frame) {
  u8g2.setFont(u8g2_font_ncenB14_tr);
  drawCentered(30, "I love you");
  u8g2.setFont(u8g2_font_ncenB10_tr);
  drawCentered(52, "Happy 20/10!");

  int r = (frame % 4 < 2) ? 4 : 3;               // little hearts pulse
  drawHeartShape(9, 10, r);
  drawHeartShape(119, 10, r);
  drawHeartShape(9, 52, r);
  drawHeartShape(119, 52, r);
}

// ---------- public API ----------

void displayBegin() {
  u8g2.begin();
  u8g2.setBusClock(400000);   // faster I2C so animation is smooth
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

void displayShowPage(uint8_t page, uint16_t frame) {
  u8g2.setPowerSave(0);
  u8g2.clearBuffer();
  switch (page) {
    case 0:  drawHeartPage(frame);    break;
    case 1:  drawGardenPage(frame);   break;
    case 2:  drawGreetingPage(frame); break;
    default: drawLovePage(frame);     break;
  }
  u8g2.sendBuffer();
}