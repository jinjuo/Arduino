/**
 * 日期: 2017/03/03
 * 作者: 
 * 描述: 
 */

#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


//显示器设置
LiquidCrystal_I2C lcd(0x20,16,2);

//软串口：Tx-D9、Rx-D8。Rx接传感器的Tx。
SoftwareSerial altSerial(8,9); 



void setup()
{
   lcd.init();                      // initialize the lcd 
        lcd.backlight();
        lcd.begin(16,2);
        Serial.begin(115200);        //USB串口向PC发送数据
    unsigned char airInit[]={0x42,0x4d,0xe1,0x00,0x00,0x01,0x71};//将传感器设置为被动模式
  Serial1.begin(9600);
  Serial1.write(airInit,7);
  delay(5000);
}

void loop()
{
    unsigned char airCommd[7]={0x42,0x4d,0xe2,0x00,0x00,0x01,0x70};
  Serial1.write(airCommd,7);//发送读取传感器数据指令
  delay(5000);
  while(Serial1.available()>0)
    {
      CopeSerialData(Serial1.read());
    }
}
char CopeSerialData(unsigned char ucData)
{
  static unsigned char ucRxBuffer[250];
  static unsigned char ucRxCnt = 0;
  long  pmcf10=0;
  long  pmcf25=0;
  long  pmcf100=0;
  long  pmat10=0;
  long  pmat25=0;
  long  pmat100=0;
  long  pmcount03=0;
  long  pmcount05=0;
  long  pmcount10=0;
  long  pmcount25=0;
  long  pmcount50=0;
  long  pmcount100=0;
  long  hcho=0;
  long  temputer=0;
  long  humidity=0;

  
  ucRxBuffer[ucRxCnt++]=ucData;

  if ((ucRxBuffer[0]!=0x42)&&(ucRxBuffer[1]!=0x4D)) 
    {
        ucRxCnt=0;
        return ucRxCnt;
    }
    
  if (ucRxCnt<40) 
  {
    return ucRxCnt;
   }
  else
  {
    for (int i=0;i<40;i++)
      {
        Serial.print(ucRxBuffer);Serial.print("  ");
       }
       int k=0;
       int l=0;
     for(int j=0;j<38;j++)
       {
           k=k+ucRxBuffer[j];
        }
        l=ucRxBuffer[38]*256+ucRxBuffer[39];
  Serial.println(""); 
  Serial.print("k=");Serial.print(k);       
  Serial.println(""); 
  Serial.print("l=");Serial.print(l);  
  Serial.println("");
  if(k==l)
  {
    pmcf10=(float)ucRxBuffer[4]*256+(float)ucRxBuffer[5];Serial.print("PM1.0_CF1:");Serial.print(pmcf10);Serial.print("   "); 
    pmcf25=(float)ucRxBuffer[6]*256+(float)ucRxBuffer[7];Serial.print("PM2.5_CF1:");Serial.print(pmcf25);Serial.print("   ");
    pmcf100=(float)ucRxBuffer[8]*256+(float)ucRxBuffer[9];Serial.print("PM10_CF1:");Serial.print(pmcf100);Serial.println("   ");
    pmat10=(float)ucRxBuffer[10]*256+(float)ucRxBuffer[11];  Serial.print("PM1.0_AT:");Serial.print(pmat10);Serial.print("   ");
    pmat25=(float)ucRxBuffer[12]*256+(float)ucRxBuffer[13];  Serial.print("PM2.5_AT:");Serial.print(pmat25);Serial.print("   ");
    pmat100=(float)ucRxBuffer[14]*256+(float)ucRxBuffer[15];  Serial.print("PM10_AT:");Serial.print(pmat100);Serial.println("   ");
    pmcount03=(float)ucRxBuffer[16]*256+(float)ucRxBuffer[17];  Serial.print("PMcount0.3:");Serial.print(pmcount03);Serial.print("   ");
    pmcount05=(float)ucRxBuffer[18]*256+(float)ucRxBuffer[19];  Serial.print("PMcount0.5:");Serial.print(pmcount05);Serial.print("   ");
    pmcount10=(float)ucRxBuffer[20]*256+(float)ucRxBuffer[21];  Serial.print("PMcount1.0:");Serial.print(pmcount10);Serial.println("   ");
    pmcount25=(float)ucRxBuffer[22]*256+(float)ucRxBuffer[23];  Serial.print("PMcount2.5:");Serial.print(pmcount25);Serial.print("   ");
    pmcount50=(float)ucRxBuffer[24]*256+(float)ucRxBuffer[25];  Serial.print("PMcount5.0:");Serial.print(pmcount50);Serial.print("   ");
    pmcount100=(float)ucRxBuffer[26]*256+(float)ucRxBuffer[27];  Serial.print("PMcount10:");Serial.print(pmcount100);Serial.println("   ");
    hcho=((float)ucRxBuffer[28]*256+(float)ucRxBuffer[29])/1000;  Serial.print("HCHO:");Serial.print(hcho);Serial.println("   ");
    temputer=(float)(float)ucRxBuffer[30]*256+(float)ucRxBuffer[31];  
    Serial.print("Temputer:");Serial.print(temputer/10);Serial.print(".");Serial.print(temputer%10);
    Serial.println("   ");
    
    humidity=((float)ucRxBuffer[32]*256+(float)ucRxBuffer[33])/10;  Serial.print("Humidity:");Serial.print(humidity);Serial.println("   ");
   for(int i=0;i<40;i++)
   {
    ucRxBuffer=0;
   }
}
  else
  {
     Serial.println("   ");
     Serial.println("Check erro!");
    }
  
Serial.println(" *****************************************************************  ");
Serial.println("   ");


  ucRxCnt=0;
  return ucRxCnt;
  
 
  
  }
}

