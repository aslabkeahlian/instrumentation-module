#include <SoftwareSerial.h>
#include <PID_v1.h>
#include <RBDdimmer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define outputPin 12
#define zerocross 2

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial mySerial(5, 7);

float ntc, hasil, hasil1, nilai_sensor;
double Setpoint, Input, Output, outval, gap;
double aggKp = 50, aggKi = 25, aggKd = 35;   // INI NILAI KP KI KD NYA DIGANTI SESUAI KEBUTUHAN

PID myPID(&Input, &Output, &Setpoint, aggKp, aggKi, aggKd, DIRECT);
dimmerLamp dimmer(outputPin);

unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  dimmer.begin(NORMAL_MODE, ON);
  myPID.SetMode(AUTOMATIC);
  
  Input = 25.0; 
  Setpoint = 50.0;
  
  mySerial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("LAB.......FISIKA");
  lcd.setCursor(0, 1);
  lcd.print("..INSTRUMENTASI.");
  delay(2000);
  lcd.clear(); 
}

void loop() {
  ntc = analogRead(A0);
  hasil = log(10000.0 * (ntc / (1023.0 - ntc)));
  hasil1 = 1 / (((0.000017 + (0.00037 * hasil)) - (0.00000031 * hasil * hasil * hasil)));
  nilai_sensor = ((float)hasil1 - 273.15);
  Input = nilai_sensor;

  gap = (Setpoint - Input);
  
  if (gap >= 0.6) {
    Output = 255;
  } 
  else if (gap < 0) {
    Output = 0;
  } 
  else {
    myPID.Compute();
  }

  if (Output <= 0) {
    outval = 0; 
  } else {
    outval = map(Output, 0, 255, 10, 80); 
  }
  dimmer.setPower(outval);

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    lcd.setCursor(0, 0);
    lcd.print("NTC = ");
    lcd.setCursor(7, 0);
    lcd.print(nilai_sensor, 1);
    lcd.print("  ");
    
    lcd.setCursor(0, 1);
    lcd.print("SP  = ");
    lcd.setCursor(7, 1);
    lcd.print(Setpoint, 1);
    lcd.print("  "); 
    mySerial.print(nilai_sensor, 1);
    mySerial.print("|");
    mySerial.print(Setpoint, 1);
    mySerial.print("|");
    mySerial.print(aggKp, 0);
    mySerial.print("|");
    mySerial.print(aggKi, 0);
    mySerial.print("|");
    mySerial.print(aggKd, 0);
    mySerial.println();
  }
}
