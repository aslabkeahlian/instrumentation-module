#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  
int koil1 = 11;
int koil2 = 10;
int koil3 = 9;
int koil4 = 8;
int i, x = 0, z = 0, y;
const int period = 15;
float putaran1, putaran2;

int putar = 2; // Jumlah putaran yang diinginkan

void setup() {
  pinMode(koil1, OUTPUT);
  pinMode(koil2, OUTPUT);
  pinMode(koil3, OUTPUT);
  pinMode(koil4, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("LAB.......FISIKA");
  lcd.setCursor(0, 1);
  lcd.print("..INSTRUMENTASI.");
  delay(1000);
  lcd.clear();
}

void loop() {
  // Hanya jalankan jika putar > 0
  if (putar > 0) {
    y = putar * 512;
    
    stepper_arah_jarum_jam();
    delay(2000);
    lcd.clear();
    
    stepper_lawan_arah_jarum_jam();
    delay(2000);
    lcd.clear();
    
    // Logika untuk memberhentikan mesin setelah 1 siklus (CW -> CCW)
    if ((x == y) && (z == y)) {
      putar = 0;  // Mesin berhenti setelah ini
    }
    
    /* 
    CATATAN: Jika Anda ingin motor memutar TERUS MENERUS (bolak-balik), 
    hapus/jadikan komentar blok "if ((x == y)..." di atas, lalu aktifkan 
    dua baris di bawah ini untuk mereset counter:
    */
    // x = 0;
    // z = 0;
  }
}

void stepper_arah_jarum_jam() {
  lcd.setCursor(0, 0);
  lcd.print("ARAH +");
  lcd.setCursor(7, 0);
  lcd.print("SP =");
  lcd.setCursor(11, 0);
  lcd.print(putar); // Perbaikan: hilangkan angka ,1

  for (i = 0; i < y; i++) {
    x++;
    digitalWrite(koil1, HIGH); digitalWrite(koil2, LOW); digitalWrite(koil3, LOW); digitalWrite(koil4, LOW); delay(period);
    digitalWrite(koil1, HIGH); digitalWrite(koil2, HIGH); digitalWrite(koil3, LOW); digitalWrite(koil4, LOW); delay(period);
    digitalWrite(koil1, LOW); digitalWrite(koil2, HIGH); digitalWrite(koil3, LOW); digitalWrite(koil4, LOW); delay(period);
    digitalWrite(koil1, LOW); digitalWrite(koil2, HIGH); digitalWrite(koil3, HIGH); digitalWrite(koil4, LOW); delay(period);
    digitalWrite(koil1, LOW); digitalWrite(koil2, LOW); digitalWrite(koil3, HIGH); digitalWrite(koil4, LOW); delay(period);
    digitalWrite(koil1, LOW); digitalWrite(koil2, LOW); digitalWrite(koil3, HIGH); digitalWrite(koil4, HIGH); delay(period);
    digitalWrite(koil1, LOW); digitalWrite(koil2, LOW); digitalWrite(koil3, LOW); digitalWrite(koil4, HIGH); delay(period);
    digitalWrite(koil1, HIGH); digitalWrite(koil2, LOW); digitalWrite(koil3, LOW); digitalWrite(koil4, HIGH); delay(period);
  }
  
  // Perbaikan: gunakan casting float agar pembagian terbaca sebagai desimal
  putaran1 = (float)x / 512.0; 
  lcd.setCursor(0, 1);
  lcd.print("PUTARAN= ");
  lcd.print(putaran1);
  
  matikan_koil(); // Matikan koil agar motor tidak panas saat jeda
  delay(3000);
}

void stepper_lawan_arah_jarum_jam() {
  lcd.setCursor(0, 0);
  lcd.print("ARAH -");
  lcd.setCursor(7, 0);
  lcd.print("SP =");
  lcd.setCursor(11, 0);
  lcd.print(putar); // Perbaikan: hilangkan angka ,1
  
  for (i = 0; i < y; i++) {
    z++;
    digitalWrite(koil1, HIGH); digitalWrite(koil2, LOW); digitalWrite(koil3, LOW); digitalWrite(koil4, HIGH); delay(period);
    digitalWrite(koil1, LOW); digitalWrite(koil2, LOW); digitalWrite(koil3, LOW); digitalWrite(koil4, HIGH); delay(period);
    digitalWrite(koil1, LOW); digitalWrite(koil2, LOW); digitalWrite(koil3, HIGH); digitalWrite(koil4, HIGH); delay(period);
    digitalWrite(koil1, LOW); digitalWrite(koil2, LOW); digitalWrite(koil3, HIGH); digitalWrite(koil4, LOW); delay(period);
    digitalWrite(koil1, LOW); digitalWrite(koil2, HIGH); digitalWrite(koil3, HIGH); digitalWrite(koil4, LOW); delay(period);
    digitalWrite(koil1, LOW); digitalWrite(koil2, HIGH); digitalWrite(koil3, LOW); digitalWrite(koil4, LOW); delay(period);
    digitalWrite(koil1, HIGH); digitalWrite(koil2, HIGH); digitalWrite(koil3, LOW); digitalWrite(koil4, LOW); delay(period);
    digitalWrite(koil1, HIGH); digitalWrite(koil2, LOW); digitalWrite(koil3, LOW); digitalWrite(koil4, LOW); delay(period);
  }
  
  // Perbaikan: gunakan casting float
  putaran2 = (float)z / 512.0;
  lcd.setCursor(0, 1);
  lcd.print("PUTARAN= ");
  lcd.print(putaran2);
  
  matikan_koil(); // Matikan koil agar motor tidak panas saat jeda
  delay(3000);
}

// Fungsi tambahan untuk mematikan semua listrik ke motor (Mencegah Overheat)
void matikan_koil() {
  digitalWrite(koil1, LOW);
  digitalWrite(koil2, LOW);
  digitalWrite(koil3, LOW);
  digitalWrite(koil4, LOW);
}
