// INI KALAU PERLU DI KALIBRASI, OPSIONAL

#include <RBDdimmer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define outputPin 12
#define zerocross 2

dimmerLamp dimmer(outputPin);
int outVal = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  dimmer.begin(NORMAL_MODE, ON);
}

void loop() {
  outVal = map(analogRead(0), 0, 1023, 0, 100);
  
  lcd.setCursor(0, 0);
  lcd.print("Out= ");
  
  lcd.setCursor(5, 0);
  lcd.print(outVal);
  lcd.print("%   "); 
  dimmer.setPower(outVal);
  delay(500);
}
