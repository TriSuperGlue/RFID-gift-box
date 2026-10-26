#include "rfid.h"
#include "config.h"
#include <SoftwareSerial.h>

static SoftwareSerial rdm(PIN_RDM_RX, PIN_RDM_TX);
static unsigned long lastReadAt = 0;
constexpr unsigned long COOLDOWN_MS = 2000;  // 2 giây

void rfidBegin() {
  rdm.begin(9600);
}

String rfidRead() {
  // Flush buffer liên tục để không tích lũy frame cũ
  while (rdm.available()) rdm.read();

  // Chặn trong cooldown
  if (millis() - lastReadAt < COOLDOWN_MS) return "";

  // Chờ đủ 14 byte
  unsigned long wait = millis();
  while (rdm.available() < 14) {
    if (millis() - wait > 100) return "";  // timeout 100ms
  }

  uint8_t buf[14];
  rdm.readBytes(buf, 14);
  while (rdm.available()) rdm.read();  // flush phần dư

  if (buf[0] != 0x02 || buf[13] != 0x03) return "";

  lastReadAt = millis();  // ghi lại thời điểm đọc thành công

  String id = "";
  for (int i = 1; i <= 10; i++) id += (char)buf[i];
  return id;
}