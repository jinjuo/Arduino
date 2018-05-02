
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
        unsigned char p0_3[2];
        unsigned char p0_5[2];
        unsigned char p1_0[2];
        unsigned char p2_5[2];
        unsigned char p5_0[2];
        unsigned char p10_0[2];
        unsigned char HOCO[2];
        unsigned char Temp[2];
        unsigned char Humi[2];                      
        unsigned char d[6];
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
        lcd.clear();
}

void loop()
{
        unsigned char c;
        char str[100];
        static int state = 0;
        static int count = 0;
        static int time=0;
//        int pm1_0, pm2_5, pm10_0;        //PM1.0、PM2.5、PM10
        long pm2_5,HOCO,Temp,Humi;
        int i;

        if (altSerial.available()) {
                c = altSerial.read();
                switch (state) {
                case 0:
                        if (0x42 == c)
                                state = 1;
                        break;
                case 1:
                        if (0x4d == c) {
                                state = 2;
                                count = 0;
                                //Serial.println(' ');
                        }
                        break;
                case 2:
                        ((unsigned char *) &panteng)[count++] = c;
                        sprintf(str, "%02X ", c);
                        //Serial.print(str);
                      //  if (count > (sizeof(panteng)-2)) {
                          if (count > 36) {
                                state = 0;
/*                              pm1_0 = panteng.pm1_0[0] * 256 + panteng.pm1_0[1];
                                pm2_5 = panteng.pm2_5[0] * 256 + panteng.pm2_5[1];
                                pm10_0 = panteng.pm10_0[0] * 256 + panteng.pm10_0[1];
*/
                                pm2_5 = (float)panteng.pm2_5[0] * 256 + (float)panteng.pm2_5[1];
                                HOCO = ((float)panteng.HOCO[0] * 256 + (float)panteng.HOCO[1])/1000;
                                Temp = ((float)panteng.Temp[0] * 256 + (float)panteng.Temp[1])/10;
                                Humi = ((float)panteng.Humi[0] * 256 + (float)panteng.Humi[1])/10;
                                
//                                sprintf(str, "%d\t%d\t%d\t%d", time++,pm1_0, pm2_5, pm10_0);
                                sprintf(str, "%d\t%d\t%d\t%d\t%d", time++, pm2_5, HOCO, Temp, Humi);
                                Serial.println(str);

                                snprintf(str,16, "PM2.5:%d    ", pm2_5);
                                //lcd.clear();
                                for (i = 0; i < strlen(str); i++) {
                                        lcd.setCursor(i, 0);
                                        lcd.print(&str[i]);
                                }
                                snprintf(str,16, "T:%d", Temp);
                                //lcd.clear();
                                for (i = 0; i < strlen(str); i++) {
                                        lcd.setCursor((i+12), 0);
                                        lcd.print(&str[i]);
                                }
                                snprintf(str,16, "HOCO:%d    ", HOCO);
                                //lcd.clear();
                                for (i = 0; i < strlen(str); i++) {
                                        lcd.setCursor(i, 1);
                                        lcd.print(&str[i]);
                                }
                                snprintf(str,16, "H:%d", Humi);
                                //lcd.clear();
                                for (i = 0; i < strlen(str); i++) {
                                        lcd.setCursor((i+12), 1);
                                        lcd.print(&str[i]);
                                }

                        }
                        break;
                default:
                        break;
                }
        }
}

