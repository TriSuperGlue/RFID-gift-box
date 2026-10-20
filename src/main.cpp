#include <Arduino.h>
#include "config.h"
#include "button.h"
#include "lock.h"
#include "display.h"

enum class State { LOCKED, UNLOCKED };

Button cardSim(PIN_CARD_SIM, INPUT_PULLUP, LOW);   // stands in for the RFID reader
Button lidSwitch(PIN_LID_SWITCH, INPUT_PULLDOWN_16, HIGH);

State state = State::LOCKED;
uint8_t page = 0;
uint16_t frame = 0;
unsigned long lastFrameAt = 0;
unsigned long pageStartedAt = 0;

bool lidIsClosed() {
  if (!USE_LID_SWITCH) return true;   // no sensor yet: assume closed
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
    lastFrameAt = 0;                  // force an immediate redraw
  }

  if (now - lastFrameAt >= FRAME_MS) {
    lastFrameAt = now;
    frame++;
    displayShowPage(page, frame);
  }
}

void setup() {
  Serial.begin(115200);
  cardSim.begin();
  if (USE_LID_SWITCH) lidSwitch.begin();
  displayBegin();
  lockBegin();
}

void loop() {
  cardSim.update();
  if (USE_LID_SWITCH) lidSwitch.update();

  bool cardTapped = cardSim.wasPressed();

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