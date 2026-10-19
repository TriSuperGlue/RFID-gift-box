#include "lock.h"
#include "config.h"
#include <Servo.h>

static Servo servo;

static void moveTo(int angle) {
  servo.attach(PIN_SERVO, 500, 2400);  // pulse range in microseconds
  servo.write(angle);
  delay(600);                          // wait for the servo to arrive
  servo.detach();                      // stop jitter and save power
}

void lockBegin() { moveTo(ANGLE_LOCKED); }
void lockOpen()  { moveTo(ANGLE_OPEN); }
void lockClose() { moveTo(ANGLE_LOCKED); }