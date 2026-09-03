#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2); // Untuk di protheus pakai LCD Address 20 dan 27 untuk di percobaan realtimenya

const int analogIn = A0;
const int sensitivitas = 66; // Sensitivitas: 185 (5A), 100 (20A), 66 (30A), sensitivitas ini dicari juga nilai mana yang sama dari tegangan masuk dan ditangkap sama lcd
const int ACSoffset = 2500;  // Tegangan offset Vcc/2 (2500 mV pada tegangan 5V)

void setup() {
  pinMode(analogIn, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("..SENSOR ARUS..");
  lcd.setCursor(0, 1);
  lcd.print("....SIMULASI....");
  delay(1000);
  lcd.clear();
}

void loop() {
  int rawValue = analogRead(analogIn);
  double voltage = (rawValue / 1023.0) * 5000.0;
  double amps = (voltage - ACSoffset) / sensitivitas;
  lcd.setCursor(0, 0);
  lcd.print("SENS ARUS ACS712");
  lcd.setCursor(0, 1);
  lcd.print("Ampere = ");
  lcd.setCursor(9, 1);
  lcd.print(amps, 2);
  lcd.setCursor(15, 1);
  lcd.print("A");
  delay(1000);
}
