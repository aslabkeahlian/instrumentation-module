#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

const byte IN1 = 13;
const byte IN2 = 12;
const byte EN_V = 10;
int sensorValue,En_value ;

void putaran_searah_jarum_jam(){
  sensorValue = analogRead(A0);
  En_value = map(sensorValue,0,1023,0,255);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(EN_V,En_value);
  lcd.setCursor(0,0);
  lcd.print("GERAK SEARAH JAM");
  lcd.setCursor(0,1);
  lcd.print("PWM = ");
  lcd.setCursor(6,1);
  lcd.print(En_value);
  delay(50);
}
void putaran_lawan_jarum_jam(){
  sensorValue = analogRead(A0);
  En_value = map(sensorValue,0,1023,0,255);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  analogWrite(EN_V,En_value);
  lcd.setCursor(0,0);
  lcd.print("GERAK LAWAN JAM");
  lcd.setCursor(0,1);
  lcd.print("PWM = ");
  lcd.setCursor(6,1);
  lcd.print(En_value);
  delay(50);
}

void stop_putaran(){
  sensorValue = analogRead(A0);
  En_value = map(sensorValue,0,1023,0,255);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  analogWrite(EN_V,En_value);
  lcd.setCursor(0,0);
  lcd.print("---STOP GERAK---");
  lcd.setCursor(0,1);
  lcd.print("PWM = ");
  lcd.setCursor(6,1);
  lcd.print(En_value);
  delay(500);
}

void setup() {
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(EN_V,OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("LAB.......FISIKA");
  lcd.setCursor(0,1);
  lcd.print("..INSTRUMENTASI.");
  delay(1000);
  lcd.clear();
}

void loop() {
  putaran_searah_jarum_jam();
  delay(10000);
  putaran_lawan_jarum_jam();
  delay(10000);
  stop_putaran();
  delay(10000);
  lcd.clear();
}
