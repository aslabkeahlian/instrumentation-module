#include "HX711.h"
#include <LiquidCrystal_I2C.h>

const int LOADCELL_DOUT_PIN = 6;
const int LOADCELL_SCK_PIN = 7;

// Inisialisasi Objek Load Cell dan LCD I2C (Alamat: 0x27, 16 Kolom, 2 Baris)
HX711 scale;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Faktor Kalibrasi
const float calibration_factor = 1759.0;

void setup() {
  Serial.begin(57600);

  // Inisialisasi Hardware
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  lcd.init();
  lcd.backlight();

  // Tampilan Awal (Splash Screen)
  lcd.setCursor(0, 0);
  lcd.print("-TIMBANGAN 1 KG-");
  lcd.setCursor(0, 1);
  lcd.print("--INISIALISASI--");
  delay(1500);
  lcd.clear();

  // Proses Kalibrasi & Tare (Pengesetan Titik Nol)
  lcd.setCursor(0, 0);
  lcd.print("---SETTING UP---");
  lcd.setCursor(0, 1);
  lcd.print("---TARE SCALE---");
  
  scale.set_scale(calibration_factor); // Memasukkan faktor kalibrasi
  scale.tare();                         // Mengnolkan pembacaan beban awal
  delay(1500);
  lcd.clear();

  // Konfirmasi Siap Membaca
  lcd.setCursor(0, 0);
  lcd.print("-----MULAI------");
  lcd.setCursor(0, 1);
  lcd.print("----MEMBACA-----");
  delay(1000);
  lcd.clear();
}

void loop() {
  // Pembacaan massa instan (1 sampel) dan massa rata-rata (10 sampel) dalam gram
  float massaInstan = scale.get_units(1);
  float massaRata   = scale.get_units(10);

  // Baris 0: Menampilkan Massa Real-Time
  lcd.setCursor(0, 0);
  lcd.print("Massa = ");
  lcd.print(massaInstan, 0);
  lcd.print(" gr   ");

  // Baris 1: Menampilkan Massa Rata-Rata
  lcd.setCursor(0, 1);
  lcd.print("Rata2 = ");
  lcd.print(massaRata, 0);
  lcd.print(" gr   ");

  delay(500);
}
