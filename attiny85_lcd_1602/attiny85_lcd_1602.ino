//#include "LiquidCrystal_I2C.h"
#include "TinyWireM.h"
#include "LiquidCrystal_attiny.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  //lcd.home();
  //lcd.print("Hello Foxie");
  display("Hello Foxie");
  //lcd.setCursor(0, 1);

}

void loop() {
  // put your main code here, to run repeatedly:

}

void displayText(String text) {
  char charBuf[16];
  text.toCharArray(sharBuf, 16);
  for (int i = 0; i < text.length(); i++) {
    lcd.print(charBuf[i]);
  }
}
