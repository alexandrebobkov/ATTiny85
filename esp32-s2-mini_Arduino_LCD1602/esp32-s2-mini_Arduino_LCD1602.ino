//#include <LCD-I2C.h>
#include <LiquidCrystal_I2C.h>
//#include "LiquidCrystal_attiny.h"

//LCD_I2C lcd(0x27, 16, 2);
LiquidCrystal_I2C lcd(0x27, 16, 2);

uint8_t snow[8] =
{
    0b01000,
    0b11101,
    0b01011,
    0b00001,
    0b00100,
    0b01110,
    0b00100,
    0b10000
};

void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  lcd.createChar(1, snow);
  lcd.clear();
  lcd.display();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" HAPPY HOLIDAYS ");
  lcd.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 1);              // Line 2
  lcd.print(" ESP32 S2 mini ");
  for (int i = 0; i < 16; i++)
  {
    lcd.scrollDisplayLeft();
    delay(200);
  }

}
