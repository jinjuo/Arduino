
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20,16,2);


void setup() {
  lcd.init();                    
  lcd.init();
  lcd.backlight();
  lcd.begin(16,2);
  Serial.begin(9600);

}

void loop() {
if(Serial.available()){
  delay(500);
  lcd.clear();
  while(Serial.available()>0){
   // lcd.print("You:");
    lcd.setCursor(0,0);
    lcd.write(Serial.read());
    }
  }

}
