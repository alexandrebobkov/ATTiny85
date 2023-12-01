/*

Arduino IDE
Board: Digispark 16.5MHz (default)

Alexander Bobkov
Nov 30, 2023

*/

#include "DigiKeyboard.h"
#include <Wire.h>

#define LED_PIN 1 // LED on Model A  4
//#define LED_PIN 0 // LED on Model B 
#define SENSOR_PIN 5

const byte I2C_SLAVE_ADDR = 0x27;

int sensor_value = 0;

void setup() {             
  // Initialize the digital pin as an output
  pinMode(LED_PIN, OUTPUT);
  Wire.begin();
}

void loop() {

  sensor_value = analogRead(SENSOR_PIN);
  DigiKeyboard.print("ATtiny85. Sensor: ");
  DigiKeyboard.println(sensor_value);
  /*Wire.beginTransmission(SENSOR_PIN);
  Wire.write(sensor_value);
  Wire.endTransmission();*/

  delay(1500); 
  digitalWrite(LED_PIN, HIGH);
  delay(250);              
  digitalWrite(LED_PIN, LOW); 
  delay(250);               
  digitalWrite(LED_PIN, HIGH);
  delay(250);                
  digitalWrite(LED_PIN, LOW); 
  delay(1500);
}
