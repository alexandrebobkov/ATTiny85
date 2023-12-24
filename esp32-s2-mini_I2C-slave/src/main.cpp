#include <Arduino.h>
#include <Wire.h>

byte receive, transmit;

void receiveEvent(int bytes) {
  while (Wire.available()) {
    receive = Wire.read();
  }
}

void requestEvent(void) {
  Wire.write(transmit);
}

void setup() {
  Wire.begin(0x20);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  
}

void loop() {
  // put your main code here, to run repeatedly:
}