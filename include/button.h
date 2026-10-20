#pragma once
#include <Arduino.h>

class Button {
 public:
  Button(uint8_t pin, uint8_t mode, bool activeLevel);
  void begin();
  void update();           // call every loop()
  bool isPressed() const;  // stable (debounced) state
  bool wasPressed();       // true once per new press
 private:
  uint8_t _pin;
  uint8_t _mode;
  bool _activeLevel;
  bool _stable;
  bool _lastRaw;
  bool _edge;
  unsigned long _lastChange;
};