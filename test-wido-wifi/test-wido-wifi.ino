/**********函数库**********/
#include <Adafruit_CC3000.h>
#include <SPI.h>
/**********引脚定义**********/
#define Wido_IRQ   7
#define Wido_VBAT  5
#define Wido_CS    10
/**********设定CC3000名称，引脚**********/
Adafruit_CC3000 Wido = Adafruit_CC3000(Wido_CS, Wido_IRQ, Wido_VBAT,
SPI_CLOCK_DIVIDER); // you can change this clock speed
/**********无线信息**********/
#define WLAN_SSID       "CU_rj2k" //这里需要改成自己的SSID
#define WLAN_PASS       "cjunt6e6" //这里需要改成自己的密码
#define WLAN_SECURITY   WLAN_SEC_WPA2 //这里需要改成自己的加密方式
  
  
void setup()
{
  Serial.begin(115200); //初始化串口，设置波特率为115200
  Serial.println(F("Hello, CC3000!\n"));//F()是表示存在Flash中
  
  Serial.println(F("\nInitialising the CC3000 ..."));
  //如果WiDo初始化失败，那么串口返回信息，进入死循环
  if (!Wido.begin())
  {
    Serial.println(F("Unable to initialise the CC3000! Check your wiring?"));
    while(1);
  }
 
  char *ssid = WLAN_SSID;
  Serial.print(F("\nAttempting to connect to "));
  Serial.println(ssid);
  
  //如果无线连接失败，串口返回数据，进入死循环
  if (!Wido.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY))
{
    Serial.println(F("Failed!"));
    while(1);
  }
  
  Serial.println(F("Connected!"));
  //等待动态IP地址
  Serial.println(F("Request DHCP"));
  while (!Wido.checkDHCP())
  {
    delay(100);
  } 
 
}
