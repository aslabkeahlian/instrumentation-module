#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial mySerial(5, 6);
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int RELAY_PIN = 3;
const int NTC_PIN = A0;
float ntc;
float hasil;
float hasil1;
float nilai_sensor;
float Setpoin = 50.0;

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  mySerial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("-KENDALI ON/OFF-");
  lcd.setCursor(0, 1);
  lcd.print("    SIMULASI    ");
  delay(2000);
  lcd.clear();
}

void loop() {
  ntc = analogRead(NTC_PIN);
  hasil = log(10000.0 * (ntc / (1023.0 - ntc)));
  hasil1 = 1.0 / (0.000017 + (0.00037 * hasil) - (0.00000031 * hasil * hasil * hasil));
  nilai_sensor = hasil1 - 273.15;

  lcd.setCursor(0, 0);
  lcd.print("NTC = ");
  lcd.print(nilai_sensor, 1);
  lcd.print(" C  ");
  lcd.setCursor(0, 1);
  lcd.print("SP  = ");
  lcd.print(Setpoin, 1);
  lcd.print(" C  ");
  mySerial.print(nilai_sensor, 1);
  mySerial.print("|");
  mySerial.println(Setpoin, 1);

  if (nilai_sensor <= Setpoin) {
    digitalWrite(RELAY_PIN, LOW);
  } else {
    digitalWrite(RELAY_PIN, HIGH);
  }

  delay(1000);
}
