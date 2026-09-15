#include <Stepper.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 

const int stepsPerRevolution = 2048;  

Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

int stepCount = 0; 
float hitung;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("-MODUL STEPPER-");
  lcd.setCursor(0,1);
  lcd.print("    SIMULASI    ");
  delay(2000);
  lcd.clear();
}
void loop() {
  myStepper.step(1);
  lcd.setCursor(0,0);
  lcd.print("STEP = ");        
  lcd.setCursor(7,0);
  lcd.print(stepCount);
  hitung =(stepCount *0.17578125);
  lcd.setCursor(0,1);
  lcd.print("DEG = ");
  lcd.setCursor(7,1);
  lcd.print(hitung);
  stepCount++;
  delay(500);
}


