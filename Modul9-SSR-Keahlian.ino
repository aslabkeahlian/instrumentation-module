#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  pinMode(10,OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("LAB.......FISIKA");
  lcd.setCursor(0,1);
  lcd.print("..INSTRUMENTASI.");
  delay(1000);
}
void loop() {
  int sensorValue = analogRead(A0);
  int Pwm_value = map(sensorValue,0,1023,0,255);
  lcd.setCursor(0,0);
  lcd.print("------SSR-------");
  lcd.setCursor(0,1);
  lcd.print("SSR = ");
  lcd.setCursor(6,1);
  lcd.print(Pwm_value);
  analogWrite(10,Pwm_value);
  delay(500);
  lcd.clear();
}
