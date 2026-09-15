// PERBEDAAN DENGAN V1 :
// Perbedaannya adalah kodingan ini membatasi gerak servonya karena panjang pulsa yg dihasilin berbeda dengan yang ditampilkan LCD
// Sebagai contoh : secara teori 1 m/s = 0º ; 1.5 m/s = 90º ; 2 m/s = 180º 
//                  realita dari osiloskop 0.5 m/s = 0º ; 1.5 m/s = 90º ; 2.5 m/s = 180º

#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Untuk di protheus pakai LCD Address 20 dan 27 untuk di percobaan realtimenya
Servo myservo;

const int potpin = A0; 
int val;               

void setup() {
  myservo.attach(9);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("--MOTOR SERVO---");
  lcd.setCursor(0, 1);
  lcd.print("    SIMULASI    ");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("--MOTOR SERVO---");
  lcd.setCursor(0, 1);
  lcd.print("Servo = ");
}

void loop() {
  val = analogRead(potpin);            
  val = map(val, 0, 1023, 0, 180);  
  myservo.write(val);                  
  lcd.setCursor(8, 1);
  lcd.print(val);
  lcd.print("   ");                    
  delay(15);                          
}
