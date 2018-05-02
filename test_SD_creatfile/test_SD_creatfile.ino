#include<SPI.h>
#include<SD.h>

File myFile;

void setup() {
  // 初始化串口通信
  Serial.begin(9600);
  while(!Serial){
    ;
    }
  Serial.println("Initializing SD card...");
 // pinMode(10,OUTPUT);
  if(!SD.begin(4)){
    Serial.println("initialization failed!");
    return;
    }
  Serial.println("initialization done!");
  if(SD.exists("arduino.txt")){
    Serial.println("arduino.txt exists."); 
    }
    else{
      Serial.println("arduino.txt doesn't exist.");
      }
  /*
  Serial.println("Creating arduino.txt...");
  SD.open("arduino.txt",FILE_WRITE);
  myFile.close();
  */
  /*  
  Serial.println("Removing arduino.txt..");
  SD.remove("arduino.txt");
  */


/*
    // 检查文件是否存在
  if(SD.exists("arduino.txt")){
    Serial.println("arduino.txt exist.");
    }
   else{
    Serial.println("arduino.txt dosen't exist.");
    } 

*/
   
    //写文件
    myFile = SD.open("arduino.txt",FILE_WRITE);
    if(myFile){
     myFile.println("HELLO WORLD");
     myFile.close();
     Serial.println("Done!");
    }else{
     Serial.println("error opening arduino.txt");
      }

    // 读文件
    myFile = SD.open("arduino.txt");
    if(myFile){
      Serial.print("arduino说:");
      while(myFile.available()){
        Serial.write(myFile.read());
        }
      myFile.close();
      }else{
        Serial.println("error opening the file...");
        }
      


}
   

void loop() {
  // put your main code here, to run repeatedly:

}
