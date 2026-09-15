#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);    // Untuk di protheus pakai LCD Address 20 dan 27 untuk di percobaan realtimenya

// Ini untuk tampilan awal LCD, hanya bisa sampai 16 karakter huruf
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" PRAK KEAHLIAN  ");    // Ganti tampilan awal baris pertama sesuai kemauan kalian
  lcd.setCursor(0, 1);
  lcd.print(" INSTRUMENTASI  ");    // Ini untuk tampilan baris keduanya
}

void loop() {
}
