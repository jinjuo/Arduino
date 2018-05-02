


//导入3个库
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


//显示器设置
LiquidCrystal_I2C lcd(0x20,16,2);

//软串口：Tx-D9、Rx-D8。Rx接传感器的Tx。
SoftwareSerial altSerial(8,9); 



//传感器的数据格式
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
        unsigned char d[11];
} panteng;  

void setup()
{
        // 初始化屏幕
        lcd.init();                       
        lcd.backlight();
        lcd.begin(16,2);
        //USB串口向PC发送数据
        Serial.begin(115200);  
        //软串口连接传感器      
        altSerial.begin(9600);        

}

void loop()
{
        unsigned char c;
        char str[100];
        static int state = 0;
        static int count = 0;
        static int time=0;
//        int pm1_0, pm2_5, pm10_0;        //PM1.0、PM2.5、PM10
        int pm2_5,HOCO,Temp,Humi;
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
                        if (count > 28) {
                                state = 0;
/*                                pm1_0 = panteng.pm1_0[0] * 256 + panteng.pm1_0[1];
                                pm2_5 = panteng.pm2_5[0] * 256 + panteng.pm2_5[1];
                                pm10_0 = panteng.pm10_0[0] * 256 + panteng.pm10_0[1];
*/
                                pm2_5 = panteng.pm2_5[0] * 256 + panteng.pm2_5[1];
                                HOCO = (panteng.HOCO[0]* 256 + panteng.HOCO[1])/1000f;
                                Temp = (panteng.Temp[0] * 256 + panteng.Temp[1])/10f;
                                Humi = (panteng.Humi[0] * 256 + panteng.Humi[1])/10f;
                                
//                                sprintf(str, "%d\t%d\t%d\t%d", time++,pm1_0, pm2_5, pm10_0);
                                sprintf(str, "%d\t%d\t%d\t%d\t%d", time++, pm2_5, HOCO, Temp, Humi);
                                Serial.println(str);

                                snprintf(str,16, "PM2.5:%d    ", pm2_5);
                                //lcd.clear();
                                for (i = 0; i < strlen(str); i++) {
                                        lcd.setCursor(i, 1);
                                        lcd.print(&str[i]);
                                }
                        }
                        break;
                default:
                        break;
                }
        }
}

