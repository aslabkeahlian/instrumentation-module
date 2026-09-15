#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  
int koil1 =11;
int koil2 =10;
int koil3 =9;
int koil4 =8;
int i, x=0,z=0, y;
const int period =15;
float putaran1,putaran2 ;
int putar = 2;

void setup() {
  pinMode(koil1,OUTPUT);
  pinMode(koil2,OUTPUT);
  pinMode(koil3,OUTPUT);
  pinMode(koil4,OUTPUT);
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
y = putar*512;
stepper_arah_jarum_jam();
delay(2000);
lcd.clear();
stepper_lawan_arah_jarum_jam();
delay(2000);
lcd.clear();
if ((x==y) && (z==y)){
putar = 0;  }
}

void stepper_arah_jarum_jam(){
  lcd.setCursor(0,0);
  lcd.print("ARAH +");
  lcd.setCursor(7,0);
  lcd.print("SP =");
  lcd.setCursor(11,0);
  lcd.print(putar,1);
  for(i=0;i<y;i++){
  x++;
  //step 1 ( 0x01H  biner 1000)
  digitalWrite(koil1,HIGH);
  digitalWrite(koil2,LOW);
  digitalWrite(koil3,LOW);
  digitalWrite(koil4,LOW);
  delay(period);
  //step2 ( 0x03H biner 1100)
  digitalWrite(koil1,HIGH);
  digitalWrite(koil2,HIGH);
  digitalWrite(koil3,LOW);
  digitalWrite(koil4,LOW);
  delay(period);
  //step3 (0x02H biner 0100)
  digitalWrite(koil1,LOW);
  digitalWrite(koil2,HIGH);
  digitalWrite(koil3,LOW);
  digitalWrite(koil4,LOW);
  delay(period);
  //step4 (0x06H biner 0110)
  digitalWrite(koil1,LOW);
  digitalWrite(koil2,HIGH);
  digitalWrite(koil3,HIGH);
  digitalWrite(koil4,LOW);
  delay(period);
  //step5 (0x04H biner 0010)
  digitalWrite(koil1,LOW);
  digitalWrite(koil2,LOW);
  digitalWrite(koil3,HIGH);
  digitalWrite(koil4,LOW);
  delay(period);
  //step6 (0x0CH biner 0011)
  digitalWrite(koil1,LOW);
  digitalWrite(koil2,LOW);
  digitalWrite(koil3,HIGH);
  digitalWrite(koil4,HIGH);
  delay(period);
  //step7 (0x08H biner 0001)
  digitalWrite(koil1,LOW);
  digitalWrite(koil2,LOW);
  digitalWrite(koil3,LOW);
  digitalWrite(koil4,HIGH);
  delay(period);
  //step8 (0x09 biner 1001)
  digitalWrite(koil1,HIGH);
  digitalWrite(koil2,LOW);
  digitalWrite(koil3,LOW);
  digitalWrite(koil4,HIGH);
  delay(period);
  }
    putaran1 = (x/512);
  lcd.setCursor(0,1);
  lcd.print("PUTARAN = ");
  lcd.setCursor(10,1);
  lcd.print(putaran1);
  digitalWrite(koil1,HIGH);
  digitalWrite(koil2,LOW);
  digitalWrite(koil3,LOW);
  digitalWrite(koil4,HIGH);
  delay(period);
  delay(3000);
}

void stepper_lawan_arah_jarum_jam(){
  lcd.setCursor(0,0);
  lcd.print("ARAH -");
  lcd.setCursor(7,0);
  lcd.print("SP =");
  lcd.setCursor(11,0);
  lcd.print(putar,1);
  lcd.setCursor(0,1);
  for(i=0;i<y;i++){
  z++;
  //step 1 ( 0x09H  biner 1001)
  digitalWrite(koil1,HIGH);
  digitalWrite(koil2,LOW);
  digitalWrite(koil3,LOW);
  digitalWrite(koil4,HIGH);
  delay(period);
  //step2 ( 0x08H biner 0001)
  digitalWrite(koil1,LOW);
  digitalWrite(koil2,LOW);
  digitalWrite(koil3,LOW);
  digitalWrite(koil4,HIGH);
  delay(period);
  //step3 (0x0CH biner 0011)
  digitalWrite(koil1,LOW);
  digitalWrite(koil2,LOW);
  digitalWrite(koil3,HIGH);
  digitalWrite(koil4,HIGH);
  delay(period);
  //step4 (0x04H biner 0010)
  digitalWrite(koil1,LOW);
  digitalWrite(koil2,LOW);
  digitalWrite(koil3,HIGH);
  digitalWrite(koil4,LOW);
  delay(period);
  //step5 (0x06H biner 0110)
  digitalWrite(koil1,LOW);
  digitalWrite(koil2,HIGH);
  digitalWrite(koil3,HIGH);
  digitalWrite(koil4,LOW);
  delay(period);
  //step6 (0x02H biner 0100)
  digitalWrite(koil1,LOW);
  digitalWrite(koil2,HIGH);
  digitalWrite(koil3,LOW);
  digitalWrite(koil4,LOW);
  delay(period);
  //step7 (0x03H biner 1100)
  digitalWrite(koil1,HIGH);
  digitalWrite(koil2,HIGH);
  digitalWrite(koil3,LOW);
  digitalWrite(koil4,LOW);
  delay(period);
  //step8 (0x01 biner 1000)
  digitalWrite(koil1,HIGH);
  digitalWrite(koil2,LOW);
  digitalWrite(koil3,LOW);
  digitalWrite(koil4,LOW);
  delay(period);
  }
  putaran2 = (z/512);
  lcd.setCursor(0,1);
  lcd.print("PUTARAN = ");
  lcd.setCursor(10,1);
  lcd.print(putaran2);
  digitalWrite(koil1,HIGH);
  digitalWrite(koil2,LOW);
  digitalWrite(koil3,LOW);
  digitalWrite(koil4,LOW);
  delay(period);
  delay(3000);
}



