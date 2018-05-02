
/** arduino leonardo
 *  ~~ 屏幕显示欢迎信息
 *  ~~ 屏幕展示传感器读取的pm2.5和HCHO数值
 *  同时将数据存储到sd卡中
 *  将数据同步到线上服务器中,服务器中可以highchart插件查看
 *  
 *  
 */
//MicroSD —D4(CS),D14(MISO),D15(SCK),D16(MOSI)


#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
// #include <SD.h>
#include <Adafruit_CC3000.h>
#include <ccspi.h>

//路由器信息配置
#define Wido_IRQ   7
#define Wido_VBAT  5
#define Wido_CS    10
Adafruit_CC3000 Wido = Adafruit_CC3000(Wido_CS, Wido_IRQ, Wido_VBAT,SPI_CLOCK_DIVIDER);
#define WLAN_SSID       "CU_rj2k"        // cannot be longer than 32 characters!
#define WLAN_PASS       "cjunt6e6"     // 
// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
#define WLAN_SECURITY   WLAN_SEC_WPA2

#define TCP_TIMEOUT      3000
#define WEBSITE  "api.xively.com"
#define API_key  "9d808f908919405dc88c040e8a12872c"  // Update Your API Key
#define DEVICEID        "359301"
#define SENSORID_P       "409166"
#define SENSORID_C       "409167"
#define SENSORID_T       "409168"
#define SENSORID_H       "409169"

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

/*
//存储数据的文件
File dataFile;
*/
uint32_t ip = 0;
float temp = 0;

void setup()
{
        lcd.init();                      // initialize the lcd 
        lcd.backlight();
        lcd.begin(16,2);
        Serial.begin(115200);        //USB串口向PC发送数据
        altSerial.begin(9600);        //软串口连接传感器
/*
        //  初始化SD卡 
        while(!altSerial){
             ;
         }
        Serial.println("Initializing SD card...");
         // pinMode(10,OUTPUT);
        if(!SD.begin(4)){
           Serial.println("initialization failed!");
           while(1);
        }
        Serial.println("SD card initialization done!");
*/
        //初始化网络
        Serial.println(F("Hello, CC3000!\n")); 
         /* Initialise the module */
        Serial.println(F("\nInitialising the CC3000 ..."));
        if (!Wido.begin()){
           Serial.println(F("Unable to initialise the CC3000! Check your wiring?"));
           while(1);
        }

        /* Attempt to connect to an access point */
        char *ssid = WLAN_SSID;             /* Max 32 chars */
        Serial.print(F("\nAttempting to connect to ")); 
        Serial.println(ssid);

        /* NOTE: Secure connections are not available in 'Tiny' mode!
        By default connectToAP will retry indefinitely, however you can pass an
        optional maximum number of retries (greater than zero) as the fourth parameter.
        */
        if (!Wido.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
           Serial.println(F("Failed!"));
           while(1);
        }

        Serial.println(F("Connected!"));

         /* Wait for DHCP to complete */
        Serial.println(F("Request DHCP"));
        while (!Wido.checkDHCP()){
           delay(100); // ToDo: Insert a DHCP timeout!
        }  


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
        
/*
        SD.remove("datalog.txt");
        Serial.println("rm done");//测试期间清除数据文件
        // 读取数据模块
        if(SD.exists("datalog.txt")){
           Serial.println("datalog.txt exists."); 
        }else{
           Serial.println("datalog.txt doesn't exist.");
        }
        File myFile;
        myFile = SD.open("datalog.txt");
        if(myFile){
          Serial.println("reading...");
          while(myFile.available()){
            Serial.write(myFile.read());
            myFile.close();
            }
          }else{
            Serial.println("error opening the file...");
            }
*/          
       
}

void loop()
{

        unsigned char c;
        char str[100];
        static int state = 0;
        static int count = 0;
        static int time=0;
        int pm2_5,HOCO,Temp,Humi;
        int i;
        
        // 建立云端连接
        static Adafruit_CC3000_Client WidoClient;
        static unsigned long RetryMillis = 0;  // timer stamp for building the connection
        static unsigned long uploadtStamp = 0; // timer stamp for posting data to service
        static unsigned long sensortStamp = 0; // timer stamp for reading data to LM35
  
        // Apply for the connection with the cloud service
        if(!WidoClient.connected() && millis() - RetryMillis > TCP_TIMEOUT){
        // Update the time stamp
           RetryMillis = millis();

           Serial.println(F("Try to connect the cloud server"));
           WidoClient.close();


            //Get Yeelink IP    
           Serial.print(F("api.yeelink.net -> "));
           while  (ip  ==  0)  {
                if  (!Wido.getHostByName(WEBSITE, &ip))  {    //  Get the server IP address based on the domain name
                Serial.println(F("Couldn't resolve!"));
               }
               delay(500);
            }  
            Wido.printIPdotsRev(ip);
            Serial.println(F(""));

            // Connect to the Yeelink Server
            WidoClient = Wido.connectTCP(ip, 80);          // Try to connect cloud server
        }
  

    
        // 传感器数据读取    
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
                        //if (count > (sizeof(panteng)-2)) {
                          if (count > 36) {
                                state = 0;
                                pm2_5 = panteng.pm2_5[0] * 256 + panteng.pm2_5[1];
                                HOCO = (panteng.HOCO[0] * 256 + panteng.HOCO[1]);
                                Temp = (panteng.Temp[0] * 256 + panteng.Temp[1])/10;
                                Humi = (panteng.Humi[0] * 256 + panteng.Humi[1])/10;
                                int HOCO_1 = HOCO/1000;
                                int HOCO_2 = HOCO % 1000;
                                sprintf(str, "%d\t%d\t%d.%03d\t%d\t%d", time++, pm2_5, HOCO_1, HOCO_2, Temp, Humi);
                                Serial.println(str);
                                //抛掉传感器带来的异常数据
                                if(time>2){
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
                                snprintf(str,16, "HCHO:%d.%03d    ", HOCO_1, HOCO_2);                           
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

                                /*
                                //向sd卡中写数据
                                Serial.println("Open file and write data");
                                File dataFile = SD.open("datalog.txt",FILE_WRITE);
                                if(dataFile){
                                   dataFile.print("PM2.5:");
                                   dataFile.print(pm2_5);
                                   dataFile.print(",");
                                   dataFile.print("HCHO:");
                                   dataFile.print(float(HOCO/1000));
                                   dataFile.print(",");
                                   dataFile.print("Temerature:");
                                   dataFile.print(Temp);
                                   dataFile.print(",");
                                   dataFile.print("Humidity:");
                                   dataFile.print(Humi);
                                   dataFile.print(",");
                                   dataFile.close();
                                }else{
                                   Serial.println("error opening datalog.txt");
                                }
                                */

                                if(WidoClient.connected() && millis() - uploadtStamp > 2000){
                                    uploadtStamp = millis();
                                    // If the device is connected to the cloud server, upload the data every 2000ms.

                                    // Prepare Http Package for Yeelink & get length
                                    int length = 0;
                                    char lengthstr[3];
    
                                    // Create Http data package
                                    char httpPackage[60] = "";
    
                                    strcat(httpPackage,"{\"value\":");
                                    itoa(temp,httpPackage+strlen(httpPackage),10);          // push the data(temp) to the http data package
                                    strcat(httpPackage,"}");
    
                                    length = strlen(httpPackage);                           // get the length of data package
                                    itoa(length,lengthstr,10);                              // convert int to char array for posting
                                    Serial.print(F("Length = "));
                                    Serial.println(length);
    
                                    Serial.println(F("Connected to Yeelink server."));
    
                                    // Send headers
                                    Serial.print(F("Sending headers"));
    
                                    WidoClient.fastrprint(F("POST /v1.0/device/"));
                                    WidoClient.fastrprint(F("100/sensor/20/datapoints"));  //Please change your device ID and sensor ID here, after creating
                                                           //Please check the link: http://www.yeelink.net/user/devices
                                                           //The example URL: http://api.yeelink.net/v1.0/device/100/sensor/20/datapoints
                                    WidoClient.fastrprintln(F(" HTTP/1.1"));
                                    Serial.print(F("."));
    
                                    WidoClient.fastrprintln(F("Host: api.yeelink.net"));
                                    Serial.print(F("."));
    
                                    WidoClient.fastrprint(F("U-ApiKey: "));
                                    WidoClient.fastrprintln(API_key);
                                    Serial.print(F("."));
    
                                    WidoClient.fastrprint("Content-Length: "); 
                                    WidoClient.fastrprintln(lengthstr);
                                    WidoClient.fastrprintln("");
                                    Serial.print(F("."));
    
                                    Serial.println(F(" done."));
                                 

                                    // Send data
                                    Serial.print(F("Sending data"));
                                    WidoClient.fastrprintln(httpPackage);

                                    Serial.println(F(" done."));
    
                                /********** Get the http page feedback ***********/
    
                                unsigned long rTimer = millis();
                                Serial.println(F("Reading Cloud Response!!!\r\n"));
                                while (millis() - rTimer < 2000) {
                                      while (WidoClient.connected() && WidoClient.available()) {
                                      char c = WidoClient.read();
                                      Serial.print(c);
                                      }
                                }
                                delay(1000);             // Wait for 1s to finish posting the data stream
                                WidoClient.close();      // Close the service connection
  
                                RetryMillis = millis();  // Reset the timer stamp for applying the connection with the service
                                }

                                if(millis() - sensortStamp > 1000){
                                   sensortStamp = millis();
                                   // read the LM35 sensor value and convert to the degrees every 100ms.

                                   int reading = analogRead(0);
                                   temp = reading *0.0048828125*100;
                                   Serial.print(F("Real Time Temp: ")); 
                                   Serial.println(temp); 
  }

  
                               
                                } //正常工作模块结束与此
                        }
                        break;
                default:
                        break;
                }
         
        }
        
}

