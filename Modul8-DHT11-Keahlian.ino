#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); // // Untuk di protheus pakai LCD Address 20 dan 27 untuk di percobaan realtimenya

void setup() {
  lcd.init();
  lcd.backlight();
  dht.begin();
  lcd.setCursor(0, 0);
  lcd.print("..DHT11 SENSOR..");
  lcd.setCursor(0, 1);
  lcd.print("....SIMULASI....");
  delay(2000);
  lcd.clear();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    lcd.setCursor(0, 0);
    lcd.print("-GAGAL MEMBACA--");
    lcd.setCursor(0, 1);
    lcd.print("---SENSOR DHT---");
    delay(2000);
    return;
  }

  lcd.setCursor(0, 0);
  lcd.print("Suhu = ");
  lcd.print(t, 1);
  lcd.setCursor(14, 0);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("RH   = ");
  lcd.print(h, 1);
  lcd.setCursor(13, 1);
  lcd.print("%RH");
  delay(2000); 
}
