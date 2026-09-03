#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2); // Untuk di protheus pakai LCD Address 20 dan 27 untuk di percobaan realtimenya

const int hallPin = 2;
const int maxCnt = 100;

void setup() {
  pinMode(hallPin, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("SENSOR H EFFECT");
  lcd.setCursor(0, 1);
  lcd.print("....SIMULASI....");
  delay(1000);
  lcd.clear();
}

void loop() {
  unsigned long start = micros();
  int old = 1;
  int cnt = 0;
  
  while (cnt < maxCnt) {
    int val = digitalRead(hallPin);
    if (!val && val != old) {
      cnt++;
    }
    old = val;
  }
  
  float seconds = (micros() - start) / 1000000.0;
  float rpm = (cnt / seconds) * 60.0;
  lcd.setCursor(0, 0);
  lcd.print("SENSOR H EFFECT ");
  lcd.setCursor(0, 1);
  lcd.print("RPM = ");
  lcd.setCursor(6, 1);
  lcd.print(rpm, 1);
  lcd.print("     ");
  delay(500);
}
