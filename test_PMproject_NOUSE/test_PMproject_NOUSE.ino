
/** arduino leonardo
 *  ~~ 屏幕显示欢迎信息
 *  屏幕展示传感器读取的pm2.5和HCHO数值
 *  同时将数据存储到sd卡中
 *  将数据同步到线上服务器中,服务器中可以highchart插件查看
 *  
 *  
 */


#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//显示器设置
LiquidCrystal_I2C lcd(0x20,16,2);

//软串口：Tx-D9、Rx-D8。Rx接传感器的Tx。
SoftwareSerial altSerial(8,9); 

//特殊显示字符设置
byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

byte smiley[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};

//攀藤G5的数据格式
struct _panteng {
        unsigned char len[2];
        unsigned char pm1_cf1[2];
        unsigned char pm2_5_cf1[2];
        unsigned char pm10_0_cf1[2];
        unsigned char pm1_0[2];
        unsigned char pm2_5[2];
        unsigned char pm10_0[2];
        unsigned char hcho[2];
        unsigned char d[20];
} panteng;  //带_是随便取的变量名,不带_的是变量别名,后面会用到,所以更简洁

void setup()
{
        lcd.init();                      // initialize the lcd 
        lcd.backlight();
        lcd.begin(16,2);
        Serial.begin(115200);        //USB串口向PC发送数据
        altSerial.begin(9600);        //软串口连接传感器

        // 屏幕展示欢迎文字
        lcd.createChar(0, heart);      // create a new character
        lcd.createChar(1, smiley);
        lcd.setCursor(0,0);         // Print a message to the lcd.
        lcd.print("I ");
        lcd.write(8); // when calling lcd.write() '0' must be cast as a byte
        lcd.print(" Nicebei! ");
        lcd.write(1);
        lcd.setCursor(2,1);
        lcd.print("loved by SQ");
        delay(5000);            // 停留5s,结束欢迎语

}

void loop()
{
        unsigned char c;
        char str[100];
        static int state = 0;
        static int count = 0;
        static int time=0;
        int pm1_0, pm2_5, pm10_0;        //PM1.0、PM2.5、PM10
        int i;

        if (altSerial.available()) {
          c = altSerial.read();
          Serial.println(c);
             
        }
}

