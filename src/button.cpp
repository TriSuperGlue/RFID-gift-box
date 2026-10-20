#include "button.h"

static const unsigned long DEBOUNCE_MS = 30;

Button::Button(uint8_t pin, uint8_t mode, bool activeLevel)
    : _pin(pin), _mode(mode), _activeLevel(activeLevel),
      _stable(false), _lastRaw(false), _edge(false), _lastChange(0) {}

void Button::begin() {
  pinMode(_pin, _mode);
  _lastRaw = _stable = (digitalRead(_pin) == _activeLevel);
}

void Button::update() {
  bool raw = (digitalRead(_pin) == _activeLevel);
  if (raw != _lastRaw) {
    _lastRaw = raw;
    _lastChange = millis();
  }
  if (raw != _stable && millis() - _lastChange >= DEBOUNCE_MS) {
    _stable = raw;
    if (_stable) _edge = true;
  }
}

bool Button::isPressed() const { return _stable; }

bool Button::wasPressed() {
  bool e = _edge;
  _edge = false;
  return e;
}