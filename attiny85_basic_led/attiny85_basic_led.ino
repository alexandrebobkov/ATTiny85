/*

Arduino IDE
Board: Digispark 16.5MHz (default)

Alexander Bobkov
Nov 30, 2023

*/

#include "DigiKeyboard.h"
#include <Wire.h>

//#define LED_PIN 1 // LED on Model A  4
//#define LED_PIN 0 // LED on Model B 
//#define SENSOR_PIN 4

unsigned int sensor_value = 0;
unsigned int LED_PIN = 1;
unsigned int SENSOR_PIN = 4;

void setup() {             
  // Initialize the digital pin as an output
  pinMode(LED_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  //Wire.begin();
}

void loop() {

  sensor_value = analogRead(SENSOR_PIN);
  /*DigiKeyboard.print("ATtiny85. Sensor: ");
  DigiKeyboard.println(sensor_value);*/

  //delay(1500);
  /*for (int n = 0; n < 3; n++)
  {
    digitalWrite(LED_PIN, HIGH);
    delay(125);        
    digitalWrite(LED_PIN, LOW); 
    delay(125);
  }*/
  for (int n = 0; n < 255; n+=5)
  {
    analogWrite(LED_PIN, n);
    delay(25);
  } 
  for (int n = 255; n >= 0; n--)
  {
    analogWrite(LED_PIN, n);
    delay(25);
  }           
  //delay(1500);
}
