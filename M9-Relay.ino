#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2); // Untuk di protheus pakai LCD Address 20 dan 27 untuk di percobaan realtimenya

void setup() {
  pinMode(13, OUTPUT)
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" AKTUATOR RELAY ");
  lcd.setCursor(0, 1);
  lcd.print("....SIMULASI....");
  delay(1000);
  lcd.clear();
}

void loop() {
  digitalWrite(13, HIGH);
  lcd.setCursor(0, 0);
  lcd.print(" ....RELAY.... ");
  lcd.setCursor(0, 1);
  lcd.print(".....AKTIF......");
  delay(3000);
  lcd.clear();

  digitalWrite(13, LOW);
  lcd.setCursor(0, 0);
  lcd.print(" ....RELAY.... ");
  lcd.setCursor(0, 1);
  lcd.print("...TDK AKTIF....");
  delay(3000);
  lcd.clear();
}
