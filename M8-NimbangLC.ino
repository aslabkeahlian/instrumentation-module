// PROSES KEDUA DARI LOADCELL
// Setelah ngekalibrasi timbangan, baru kita bisa menggunakan timbangan seperti biasa dengan kodingan ini

#include "HX711.h"
#include <LiquidCrystal_I2C.h>

const int LOADCELL_DOUT_PIN = 6;
const int LOADCELL_SCK_PIN = 7;

HX711 scale;
LiquidCrystal_I2C lcd(0x27,16,2);  // Untuk di protheus pakai LCD Address 20 dan 27 untuk di percobaan realtimenya

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("SENSOR LOADCELL.");
  lcd.setCursor(0,1);
  lcd.print("....SIMULASI....");
  delay(2000);
  lcd.clear();
  delay(500);
  lcd.setCursor(0,0);
  lcd.print("----SEBELUM----");
  lcd.setCursor(0,1);
  lcd.print("---SETTING  UP--");
  delay(500);
  lcd.clear();
  delay(500);
  lcd.setCursor(0,0);
  lcd.print("DT =");
  lcd.setCursor(5,0);
  lcd.print(scale.read());
  lcd.setCursor(0,1);
  lcd.print("DTV=");
  lcd.setCursor(5,1);
  lcd.print(scale.read_average(20));
  delay(500);
  lcd.clear();
  delay(500);
  lcd.setCursor(0,0);
  lcd.print("Nilai=");
  lcd.setCursor(7,0);
  lcd.print(scale.get_value(5));
  lcd.setCursor(0,1);
  lcd.print("UNIT =");
  lcd.setCursor(7,1);
  lcd.print(scale.get_units(5),1);
  delay(500);
  scale.set_scale(1759.f); // Ini nilai kalibrasi sesuain dengan kodingan sebelumnya
  scale.tare();
  lcd.clear();
  delay(500);
  lcd.setCursor(0,0);
  lcd.print("-----SETELAH----");
  lcd.setCursor(0,1);
  lcd.print("---SETTING  UP--");
  delay(500);
  lcd.clear();
  delay(500);
  lcd.setCursor(0,0);
  lcd.print("DT =");
  lcd.setCursor(5,0);
  lcd.print(scale.read());
  lcd.setCursor(0,1);
  lcd.print("DTV=");
  lcd.setCursor(5,1);
  lcd.print(scale.read_average(20));
  delay(500);
  lcd.clear();
  delay(500);
  lcd.setCursor(0,0);
  lcd.print("Nilai=");
  lcd.setCursor(7,0);
  lcd.print(scale.get_value(5));
  lcd.setCursor(0,1);
  lcd.print("UNIT =");
  lcd.setCursor(7,1);
  lcd.print(scale.get_units(5),1);
  delay(500);
  lcd.clear();
  delay(500);
  lcd.setCursor(0,0);
  lcd.print("-----MULAI------");
  lcd.setCursor(0,1);
  lcd.print("----MEMBACA-----");
  delay(500);
  lcd.clear();
}

void loop() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Massa =");
  lcd.setCursor(7,0);
  lcd.print(scale.get_units(1),0);
  lcd.setCursor(14,0);
  lcd.print("gr");
  lcd.setCursor(0,1);
  lcd.print("Rata2 =");
  lcd.setCursor(7,1);
  lcd.print(scale.get_units(10),0);
  lcd.setCursor(14,1);
  lcd.print("gr");
  scale.power_down();  
  delay(5000);
  scale.power_up();
}
