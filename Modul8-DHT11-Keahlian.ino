#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); // 

void setup() {
  lcd.init();
  lcd.backlight();
  dht.begin();

  // Tampilan Awal (Splash Screen)
  lcd.setCursor(0, 0);
  lcd.print("..DHT11 SENSOR..");
  lcd.setCursor(0, 1);
  lcd.print("....SIMULASI....");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Membaca kelembaban dan suhu
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Memeriksa jika pembacaan sensor gagal
  if (isnan(h) || isnan(t)) {
    lcd.setCursor(0, 0);
    lcd.print("-GAGAL MEMBACA--");
    lcd.setCursor(0, 1);
    lcd.print("---SENSOR DHT---");
    delay(2000);
    return;
  }

  // Baris 1: Menampilkan Suhu
  lcd.setCursor(0, 0);
  lcd.print("Suhu = ");
  lcd.print(t, 1);
  lcd.setCursor(14, 0);
  lcd.print("C");

  // Baris 2: Menampilkan Kelembaban
  lcd.setCursor(0, 1);
  lcd.print("RH   = ");
  lcd.print(h, 1);
  lcd.setCursor(13, 1);
  lcd.print("%RH");

  delay(2000); // Sensor DHT11 membutuhkan jeda pembacaan minimal 1-2 detik
}
