#pragma once
#include <Arduino.h>

void rfidBegin();
String rfidRead();   // trả về ID nếu đọc được thẻ, "" nếu không