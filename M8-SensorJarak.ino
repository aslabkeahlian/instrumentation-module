#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2); // Untuk di protheus pakai LCD Address 20 dan 27 untuk di percobaan realtimenya

// pastiin Pin nya 9 dan 10, tapi bisa diganti juga terserah mau Pin berapa.
const int trigPin = 9;
const int echoPin = 10;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("..SENSOR JARAK..");
  lcd.setCursor(0, 1);
  lcd.print("....SIMULASI....");
  delay(2000);
  lcd.clear();
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  lcd.setCursor(0, 0);
  lcd.print("..JARAK OBJEK...");
  lcd.setCursor(0, 1);
  lcd.print("Jarak = ");
  lcd.setCursor(8, 1);
  lcd.print(distance);
  lcd.setCursor(14, 1);
  lcd.print("cm ");
  delay(500);
}
