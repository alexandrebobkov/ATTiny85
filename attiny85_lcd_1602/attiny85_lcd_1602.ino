/*
  By: Alexander Bobkov
  
  Created: December 18, 2023

  ATtiny85 displays text on LCD 1602 over I2C bus (ATtiny85 is set as Master).
  
*/
#include "TinyWireM.h"
#include "LiquidCrystal_attiny.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  //lcd.setContrast(80);
  lcd.setCursor(0, 0);              // Line 1
  displayText("Hello Foxie");
  lcd.setCursor(0, 1);              // Line 2
  displayText("I love you");
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
