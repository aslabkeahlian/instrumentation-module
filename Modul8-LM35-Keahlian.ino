#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2); // Untuk di protheus pakai LCD Address 20 dan 27 untuk di percobaan realtimenya

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("..LM35 SENSOR..");
  lcd.setCursor(0, 1);
  lcd.print("....SIMULASI....");
  delay(2000);
  lcd.clear(); 
}

void loop() {
  float sensorValue = analogRead(A0) * 0.48875; // kalau bermasalah pinoutnya bisa diganti jadi A1 atau A(n)
  lcd.setCursor(0, 0);
  lcd.print("--SUHU (LM-35)--");
  lcd.setCursor(0, 1);
  lcd.print("Suhu = ");
  lcd.setCursor(8, 1);
  lcd.print(sensorValue, 0);
  lcd.setCursor(15, 1);
  lcd.print("C");
  delay(500);
  lcd.clear();
}
