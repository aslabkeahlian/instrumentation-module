#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Untuk di proteus pakai LCD Address 0x20 dan 0x27 untuk di percobaan realtimenya

const int hallPin = 2;
const int maxCnt = 100;
const unsigned long timeoutMicros = 500000UL;

void setup() {
  pinMode(hallPin, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("SENSOR EFEK HALL");
  lcd.setCursor(0, 1);
  lcd.print("    SIMULASI    ");
  delay(1000);
  lcd.clear();
}

void loop() {
  unsigned long start = micros();
  unsigned long lastPulseTime = start;
  int old = 1;
  int cnt = 0;
  bool alatMati = false;

  while (cnt < maxCnt) {
    int val = digitalRead(hallPin);

    if (!val && val != old) {
      cnt++;
      lastPulseTime = micros();
    }
    old = val;

    if (micros() - lastPulseTime > timeoutMicros) {
      alatMati = true;
      break;
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("SENSOR EFEK HALL");
  lcd.setCursor(0, 1);

  if (alatMati) {
    lcd.print("   ALAT MATI   ");
  } else {
    float seconds = (micros() - start) / 1000000.0;
    float rpm = (cnt / seconds) * 60.0;
    lcd.print("RPM = ");
    lcd.setCursor(6, 1);
    lcd.print(rpm, 1);
    lcd.print("     ");
  }

  delay(200);
}
