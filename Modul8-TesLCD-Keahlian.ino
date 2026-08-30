#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);    // Untuk di protheus pakai 20

void setup() {
  lcd.init();
  lcd.backlight();

  // Tampilan Baris 1
  lcd.setCursor(0, 0);
  lcd.print("LAB.......FISIKA");

  // Tampilan Baris 2
  lcd.setCursor(0, 1);
  lcd.print("..INSTRUMENTASI.");
}

void loop() {
  // Kosong karena tampilan statis
}
