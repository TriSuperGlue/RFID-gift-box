#include <Arduino.h>
#include "lock.h"
#include "display.h"

void setup() {
  Serial.begin(115200);
  displayBegin();
  lockBegin();
}

void loop() {
  displayText("Opening...", "");
  lockOpen();
  delay(2000);

  displayText("Closing...", "");
  lockClose();
  delay(2000);
}