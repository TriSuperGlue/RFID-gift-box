#include <Arduino.h>
#include "config.h"
#include "button.h"
#include "lock.h"
#include "display.h"

enum class State { LOCKED, UNLOCKED };

Button pageButton(PIN_PAGE_BUTTON, INPUT_PULLUP, LOW);
Button cardSim(PIN_CARD_SIM, INPUT_PULLUP, LOW);   // stands in for the RFID reader
Button lidSwitch(PIN_LID_SWITCH, INPUT_PULLDOWN_16, HIGH);

State state = State::LOCKED;
uint8_t page = 0;

bool lidIsClosed() {
  if (!USE_LID_SWITCH) return true;   // no sensor yet: assume closed
  return lidSwitch.isPressed();
}

void unlockBox() {
  lockOpen();
  page = 0;
  displayShowPage(page);
  state = State::UNLOCKED;
  Serial.println("UNLOCKED");
}

void lockBox() {
  displayOff();
  lockClose();
  state = State::LOCKED;
  Serial.println("LOCKED");
}

void setup() {
  Serial.begin(115200);
  pageButton.begin();
  cardSim.begin();
  if (USE_LID_SWITCH) lidSwitch.begin();
  displayBegin();
  lockBegin();
}

void loop() {
  pageButton.update();
  cardSim.update();
  if (USE_LID_SWITCH) lidSwitch.update();

  bool cardTapped = cardSim.wasPressed();

  switch (state) {
    case State::LOCKED:
      pageButton.wasPressed();   // discard presses made while locked
      if (cardTapped) unlockBox();
      break;

    case State::UNLOCKED:
      if (pageButton.wasPressed()) {
        page = (page + 1) % displayPageCount();
        displayShowPage(page);
      }
      if (cardTapped) {
        if (lidIsClosed()) lockBox();
        else Serial.println("Close the lid first");
      }
      break;
  }
}