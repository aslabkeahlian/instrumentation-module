// PERBEDAAN DENGAN V2 :
// Perbedaannya adalah kodingan ini membatasi gerak servonya karena panjang pulsa yg dihasilin berbeda dengan yang ditampilkan LCD
// Sebagai contoh : secara teori 1 m/s = 0º ; 1.5 m/s = 90º ; 2 m/s = 180º 
//                  realita dari osiloskop 0.5 m/s = 0º ; 1.5 m/s = 90º ; 2.5 m/s = 180º

#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,16,2);  // Untuk di protheus pakai LCD Address 20 dan 27 untuk di percobaan realtimeny
Servo myservo;
int val =0;
int Servo_value,Servo_value1 =0;

void setup() {
  myservo.attach(9);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("--MOTOR SERVO---");
  lcd.setCursor(0,1);
  lcd.print("    SIMULASI    ");
  delay(1000);
  lcd.clear();
}
void loop() {
  val = analogRead(A0);
  Servo_value = map(val,0,1023,44,142);
  Servo_value1= map(Servo_value,44,142,0,180);
  myservo.write(Servo_value ); 
  lcd.setCursor(0,0);
  lcd.print("--MOTOR SERVO---");
  lcd.setCursor(0,1);
  lcd.print("Servo = ");
  lcd.setCursor(7,1);
  lcd.print(Servo_value1);
  delay(500);
  lcd.clear();
}
