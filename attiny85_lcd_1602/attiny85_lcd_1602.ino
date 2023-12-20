/*
  By: Alexander Bobkov
  
  Created: December 18, 2023

  ATtiny85 displays text on LCD 1602 over I2C bus (ATtiny85 is set as Master).
  
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "TinyWireM.h"
#include "LiquidCrystal_attiny.h"

#define INTERRUPT_PIN PCINT1  // This is PB1 per the schematic
#define INT_PIN PB1           // Interrupt pin of choice: PB1 (same as PCINT1) - Pin 6
#define LED_PIN PB4           // PB4 - Pin 3
#define PCINT_VECTOR PCINT0_vect      // This step is not necessary - it's a naming thing for clarit

uint8_t toggle = false;
uint8_t state_prev = false;
uint8_t state_curr = false;


LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  //lcd.setContrast(80);
  lcd.setCursor(0, 0);              // Line 1
  //displayText("Hello Foxie");
  //lcd.autoscroll();
  displayText(" HAPPY HOLIDAYS");
  lcd.setCursor(0, 1);              // Line 2
  //displayText("I love you");
  displayText(" EIT  2023/2024");

  // Setup Interrupts
  pinMode(LED_PIN, OUTPUT);
  cli();                            // Disable interrupts during setup
  PCMSK |= (1 << INTERRUPT_PIN);    // Enable interrupt handler (ISR) for our chosen interrupt pin (PCINT1/PB1/pin 6)
  GIMSK |= (1 << PCIE);             // Enable PCINT interrupt in the general interrupt mask
  pinMode(INT_PIN, INPUT_PULLUP);   // Set our interrupt pin as input with a pullup to keep it stable
  sei();  
}

void loop() {
  // put your main code here, to run repeatedly:

}

void displayText(String text) {
  char charBuf[16];
  text.toCharArray(charBuf, 16);
  for (int i = 0; i < text.length(); i++) {
    lcd.print(charBuf[i]);
  }
}

ISR(PCINT_VECTOR) {
  state_curr = digitalRead(INT_PIN);
  if (state_curr != state_prev) {
    state_prev = state_curr;
    if (!state_curr) {
      toggle = (toggle) ? LOW : HIGH;
      digitalWrite(LED_PIN, toggle);
    }
    if (toggle)
      lcd.backlight();
    else
      lcd.noBacklight();
  }
}
