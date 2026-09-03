#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2); // Untuk di protheus pakai LCD Address 20 dan 27 untuk di percobaan realtimenya

void setup() {
  pinMode(7, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("SENSOR INFRARED");
  lcd.setCursor(0, 1);
  lcd.print("....SIMULASI....");
  delay(2000);
  lcd.clear();
}

void loop() {
  byte sensorValue = digitalRead(7);
  lcd.setCursor(0, 0);
  if (sensorValue == HIGH) {
    lcd.print("...TERDETEKSI...");
    lcd.setCursor(0, 1);
    lcd.print(".....OBJEK......");
  } else {
    lcd.print(".TDK TERDETEKSI.");
    lcd.setCursor(0, 1);
    lcd.print(".....OBJEK......");
  }

  delay(500);
  lcd.clear();
}
