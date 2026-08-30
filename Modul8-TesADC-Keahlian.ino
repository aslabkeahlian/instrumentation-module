#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2); // Untuk di protheus pakai LCD Address 20 dan 27 untuk di percobaan realtimenya

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("LAB.......FISIKA");
  lcd.setCursor(0, 1);
  lcd.print("..INSTRUMENTASI.");
  delay(1000);
  lcd.clear();
}

void loop() {
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);
  lcd.setCursor(0, 0);
  lcd.print("ADC = ");
  lcd.setCursor(7, 0);
  lcd.print(voltage, 2);
  lcd.setCursor(15, 0);
  lcd.print("V");
  lcd.setCursor(0, 1);
  lcd.print("BitSensor = ");
  lcd.setCursor(12, 1);
  lcd.print(sensorValue);
  delay(500);
  lcd.clear();
}
