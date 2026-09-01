#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

LiquidCrystal_I2C lcd(0x20, 16, 2); // Untuk di protheus pakai LCD Address 20 dan 27 untuk di percobaan realtimenya

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("..NTC SENSOR..");
  lcd.setCursor(0, 1);
  lcd.print("....SIMULASI....");
  delay(1000);
  lcd.clear();
}

void loop() {
  float sensorValue = analogRead(A0);
  float hasil = log(10000.0 * (sensorValue / (1023.0 - sensorValue)));
  float hasil1 = 1.0 / (0.000853 + (0.000282 * hasil) - (0.00000012 * hasil * hasil * hasil));
  float result = hasil1 - 273.15; // Konversi dari Kelvin ke Celcius

  lcd.setCursor(0, 0);
  lcd.print("--SUHU (NTC)-- ");
  lcd.setCursor(0, 1);
  lcd.print("Suhu = ");
  lcd.setCursor(8, 1);
  lcd.print(result, 1);
  lcd.setCursor(15, 1);
  lcd.print("C");
  delay(500);
  lcd.clear();
}
