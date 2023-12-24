#include <Arduino.h>
#include <Wire.h>

byte receive;

void receiveEvent(int bytes) {
  while (Wire.available()) {
    receive = Wire.read();
  }
}

void setup() {
  Wire.begin(0x20);
  Wire.onReceive(receiveEvent);
  
}

void loop() {
  // put your main code here, to run repeatedly:
}