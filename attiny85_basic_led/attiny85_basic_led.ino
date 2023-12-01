#include "DigiKeyboard.h" 

#define LED_PIN 1 // LED on Model A  
//#define LED_PIN 0 // LED on Model B 
#define SENSOR_PIN 3

int sensor_value = 0;

void setup() {                
  // Initialize the digital pin as an output
  pinMode(LED_PIN, OUTPUT); 
}

void loop() {

  sensor_value = analogRead(SENSOR_PIN);
  DigiKeyboard.print("ATtiny85: ");
  DigiKeyboard.print(sensor_value);

  //digitalWrite(0, HIGH);   
  digitalWrite(LED_PIN, HIGH);
  delay(250);             
  //digitalWrite(0, LOW);    
  digitalWrite(LED_PIN, LOW); 
  delay(250);             
  //digitalWrite(0, HIGH);   
  digitalWrite(LED_PIN, HIGH);
  delay(250);             
  //digitalWrite(0, LOW);    
  digitalWrite(LED_PIN, LOW); 
  delay(1500);
}
