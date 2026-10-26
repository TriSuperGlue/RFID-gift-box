#include <Arduino.h>
#include "config.h"
#include "button.h"
#include "rfid.h"
#include "lock.h"
#include "display.h"

enum class State { LOCKED, UNLOCKED };

Button lidSwitch(PIN_LID_SWITCH, INPUT_PULLUP, LOW);

State state = State::LOCKED;
uint8_t page = 0;
uint16_t frame = 0;
unsigned long lastFrameAt = 0;
unsigned long pageStartedAt = 0;

bool lidIsClosed() {
  if (!USE_LID_SWITCH) return true;
  return lidSwitch.isPressed();
}

void unlockBox() {
  lockOpen();
  page = 0;
  frame = 0;
  pageStartedAt = millis();
  lastFrameAt = pageStartedAt;
  displayShowPage(page, frame);
  state = State::UNLOCKED;
  Serial.println("UNLOCKED");
}

void lockBox() {
  displayOff();
  lockClose();
  state = State::LOCKED;
  Serial.println("LOCKED");
}

void updateSlideshow() {
  unsigned long now = millis();

  if (now - pageStartedAt >= PAGE_MS) {
    page = (page + 1) % displayPageCount();
    pageStartedAt = now;
    frame = 0;
    lastFrameAt = 0;
  }

  if (now - lastFrameAt >= FRAME_MS) {
    lastFrameAt = now;
    frame++;
    displayShowPage(page, frame);
  }
}

void setup() {
  Serial.begin(115200);
  if (USE_LID_SWITCH) lidSwitch.begin();
  rfidBegin();
  displayBegin();
  lockBegin();
  Serial.println("Ready. Tap card...");
}

void loop() {
  if (USE_LID_SWITCH) lidSwitch.update();

  String card = rfidRead();
  bool cardTapped = (card == CARD_ID);

  if (card.length() > 0) {
    Serial.print("Card: ");
    Serial.println(card);
  }

  switch (state) {
    case State::LOCKED:
      if (cardTapped) unlockBox();
      break;

    case State::UNLOCKED:
      updateSlideshow();
      if (cardTapped) {
        if (lidIsClosed()) lockBox();
        else Serial.println("Close the lid first");
      }
      break;
  }
}