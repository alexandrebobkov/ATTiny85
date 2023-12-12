/*

  Arduino IDE
  ATTiny85
  Board: Digispark 16.5MHz (default)

  OR

  Board: ATtiny 25/45/85
  Clock: Internal 1MHz
  Processor: ATTiny85
  Programmer: USBtinyISP
  Sketch -> Upload Using Programmer


  By:     Alexander Bobkov
  Date:   Nov 30, 2023
  Update: Dec 10, 2023

  About:  Basic program written for ATTiny85 that sends data (sensor value) over I2C to a master device.

  Notes:  Use Logic 2 viewer to see data being transmitted over I2C.

*/

//#include "DigiKeyboard.h"
#include <Arduino.h>
//#include <TinyWireM.h>
#include <TinyWireS.h>
//#include <LiquidCrystal_I2C.h>

// I2C address
uint8_t address = 10;

// Peripheral sensor variables
unsigned int sensor_value = 0;
uint8_t sensor_raw = 0;
uint8_t data = 1;
bool inc = true;

// Built-in LEDs
unsigned int LED_SYS_PIN = 0;
unsigned int LED_PIN = 3;
//int SENSOR_PIN = A2; //4;



void setup() {        
  // Initialize the digital pin as an output
  pinMode(LED_PIN, OUTPUT);
//  pinMode(SENSOR_PIN, INPUT);
  // Initialize I2C slave device at given address.
  TinyWireS.begin(address);
  //TinyWireS.onRequest(requestEvent);
}

void loop() {

  //sensor_value = analogRead(SENSOR_PIN);
  //sensor_raw = analogRead(SENSOR_PIN);

  // LED pulse blink.
  digitalWrite(LED_PIN, HIGH);
  delay(250);
  digitalWrite(LED_PIN, LOW);
  delay(250);
  digitalWrite(LED_PIN, HIGH);
  delay(250);
  digitalWrite(LED_PIN, LOW);
  delay(250);
  // Send value between 0 and 10, depending on a cycle iterration
  if (data <= 10)        
    data++;
  else
    data = 0;
  // Delay 0.5 second
  TinyWireS.send(data);
  TinyWireS.available();
  delay(500);
}

void requestEvent() {}
