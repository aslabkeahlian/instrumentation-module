// PROSES PERTAMA DARI LOADCELL
// Dikodingan ini, kita ngekalibrasi dulu timbangan dengan berat benda yang mau ditimbang.

#include "HX711.h"
#include <LiquidCrystal_I2C.h>

const int LOADCELL_DOUT_PIN = 6;
const int LOADCELL_SCK_PIN = 7;

HX711 scale;
LiquidCrystal_I2C lcd(0x27,16,2); // Untuk di protheus pakai LCD Address 20 dan 27 untuk di percobaan realtimenya

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  lcd.init();
  lcd.backlight();
}

void loop() {

  if (scale.is_ready()) {
    scale.set_scale();    
    Serial.println("Tare... remove any weights from the scale.");
    lcd.setCursor(0,0);
    lcd.print("Tare .. No Beban");
    delay(5000);
    lcd.clear();
    scale.tare();
    Serial.println("Tare done...");
    lcd.setCursor(0,0);
    lcd.print("Tare ... Selesai");
    Serial.print("Place a known weight on the scale...");
    lcd.setCursor(0,1);
    lcd.print("Tempatkan..Massa");
    delay(5000);
    lcd.clear();
    long reading = scale.get_units(10);
    Serial.print("Result: ");
    Serial.println(reading);
    lcd.setCursor(0,0);
    lcd.print("Hasil :");
    lcd.setCursor(8,0);
    lcd.print(reading);
    delay(10000);
    lcd.clear();
  } 
  else {
    Serial.println("HX711 not found.");
    lcd.setCursor(0,0);
    lcd.print("......HX711.....");
    lcd.setCursor(0,1);
    lcd.print("Tidak Terdeteksi");
  }
  delay(1000);
}

//Faktor kalibrasinya dicari dari (hasil pembacaan)/(berat benda)
