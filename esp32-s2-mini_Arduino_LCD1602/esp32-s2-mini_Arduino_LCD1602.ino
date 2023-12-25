#include <LCD-I2C.h>

LCD_I2C lcd(0x27, 16, 2);

// 40 pixels
uint8_t char1 [8] = {
  0b00001,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
uint8_t pixel;

void setup() {
  // put your setup code here, to run once:

  lcd.begin();
  lcd.clear();
  lcd.display();
  lcd.backlight();
  lcd.setCursor(0, 0);   // Line 1, column 1
  //lcd.write(0);
  lcd.print(" HAPPY HOLIDAYS ");
  //lcd.displayOff();  
  
  lcd.createChar(0, char1);
  lcd.setCursor(1, 1);
  lcd.write(0);

  delay(500);
  pixel = char1[0];
  pixel << 1;
  char1[1] = pixel;
  lcd.createChar(1, char1);
  lcd.setCursor(2, 1);
  lcd.write(1);
  delay(500);

  pixel = char1[0];
  pixel << 4;
  char1[3] = pixel;
  lcd.createChar(2, char1);
  lcd.setCursor(3, 1);
  lcd.write(2);
}

void loop() {

  delay(1000);

  for (int i = 0; i < 125; i++) {
    //lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("0x");
    delay(500);
  }
  // put your main code here, to run repeatedly:
  /*lcd.setCursor(0, 1);              // Line 2
  lcd.print(" ESP32 S2 mini ");
  for (int i = 0; i < 16; i++)
  {
    lcd.scrollDisplayLeft();
    delay(200);
  }*/

  

}
