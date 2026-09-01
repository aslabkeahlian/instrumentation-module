#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2); // // Untuk di protheus pakai LCD Address 20 dan 27 untuk di percobaan realtimenya

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("..LDR SENSOR..");
  lcd.setCursor(0, 1);
  lcd.print("....SIMULASI....");
  delay(1000);
  lcd.clear();
}

void loop() {
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);
  lcd.setCursor(0, 0);
  lcd.print("ADC = ");
  lcd.print(voltage, 2);
  lcd.setCursor(15, 0);
  lcd.print("V");
  lcd.setCursor(0, 1);
  lcd.print("Lumen = ");
  lcd.print(sensorValue);
  lcd.setCursor(15, 1);
  lcd.print("L");

  delay(500);
  lcd.clear();
}
