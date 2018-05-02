
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20,16,2);


void setup() {
  lcd.init();                    
  lcd.init();
  lcd.backlight();
  lcd.begin(16,2);
  Serial.begin(9600);
  lcd.print("Hello,Nicebei!");
  delay(1000);

}

void loop() {
  for(int positionCounter = 0; positionCounter<13;positionCounter++){
    lcd.scrollDisplayLeft();
    delay(300);
    }
  for(int positionCounter = 0;positionCounter<29;positionCounter++){
    lcd.scrollDisplayRight();
    delay(300);
    }
  for(int positionCounter =0;positionCounter<16;positionCounter++){
    lcd.scrollDisplayLeft();
    delay(300);
    }
    delay(3000);
    }
  

