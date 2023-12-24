#include <LCD-I2C.h>

LCD_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:

  lcd.begin();
  lcd.clear();
  lcd.display();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.write(0);
  lcd.print(" HAPPY HOLIDAYS ");  
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
