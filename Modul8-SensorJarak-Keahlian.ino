#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi LCD I2C (Alamat: 0x20, 16 Kolom, 2 Baris)
LiquidCrystal_I2C lcd(0x20, 16, 2);

// Pin Sensor Ultrasonik HC-SR04
const int trigPin = 9;
const int echoPin = 10;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.init();
  lcd.backlight();

  // Tampilan awal (splash screen)
  lcd.setCursor(0, 0);
  lcd.print("LAB.......FISIKA");
  lcd.setCursor(0, 1);
  lcd.print("..INSTRUMENTASI.");
  delay(1000);
  lcd.clear();
}

void loop() {
  // Pemicuan sinyal ultrasonik (Trig)
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Membaca durasi pantulan gelombang (Echo)
  long duration = pulseIn(echoPin, HIGH);

  // Menghitung jarak (kecepatan suara = 0.034 cm/us)
  int distance = duration * 0.034 / 2;

  // Menampilkan data pada LCD
  lcd.setCursor(0, 0);
  lcd.print("..JARAK OBJEK...");
  
  lcd.setCursor(0, 1);
  lcd.print("Jarak = ");
  lcd.setCursor(8, 1);
  lcd.print(distance);
  lcd.setCursor(14, 1);
  lcd.print("cm "); // Spasi ekstra untuk menghapus sisa digit lama

  delay(500);
}
