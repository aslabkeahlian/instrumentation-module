#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);  // Untuk di protheus pakai LCD Address 20 dan 27 untuk di percobaan realtimenya

const int analogIn = A0;

void setup() {
  pinMode(analogIn, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("..SENSOR TEGANGAN..");
  lcd.setCursor(0, 1);
  lcd.print("....SIMULASI....");
  delay(1000);
  lcd.clear();
}

void loop() {
  int rawValue = analogRead(analogIn);
  float voltage = rawValue * (5.0 / 1023.0);
  lcd.setCursor(0, 0);
  lcd.print("SENSOR TEGANGAN ");
  lcd.setCursor(0, 1);
  lcd.print("Teg = ");
  lcd.setCursor(6, 1);
  lcd.print(voltage, 2); // Menampilkan tegangan dengan 2 angka desimal
  lcd.setCursor(15, 1);
  lcd.print("V");
  delay(1000);
}
