//Using 12864 lcd to display the output of PMS1003
#include "U8glib.h"
U8GLIB_SSD1306_132X64 u8g(10, 9, 12, 11, 13);
//                        D0, D1,CS, DC, RST

void u8g_prepare(void) {
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}

int xyz=123;//传感器的值被赋值给变量xyz;

void u8g_drawxyz(){

  int x=xyz/100; //变量xyz被拆分并分为3个值分别显示
  int y=xyz%100;
  int z=y%10;
  y=y/10;
  char s_x[2]=" ";
  char s_y[2]=" ";
  char s_z[2]=" ";
  s_x[0]=x+48;
  s_y[0]=y+48;
  s_z[0]=z+48;

  u8g.setScale2x2();//大字体
  if(x>0){ //消除第一位为0时的显示问题
    u8g.drawStr(20,12,s_x);
    u8g.drawStr(30,12,s_y);
    u8g.drawStr(40,12,s_z);
  }
  if(x==0){
    if(y==0){
      u8g.drawStr(40,12,s_z);
    }
    u8g.drawStr(30,12,s_y);
    u8g.drawStr(40,12,s_z);
  } 
  u8g.undoScale();  


}

void ProcessSerialData()//读取PMS1003的数据。并根据通信协议转化成有效的值。
{
  uint8_t mData = 0;
  uint8_t i = 0;
  uint8_t mPkt[32] = {0};
  int mCheck = 0;
while (Serial.available() > 0) 
  {  
    //Basing on the protocol of Plantower PMS1003
    mData = Serial.read();     
    delay(2);//wait until packet is received
    if(mData == 0x42)//head1 ok
     {
        mPkt[0] =  mData;
        mData = Serial.read();
        if(mData ==0x4d)//head2 ok
        {
          mPkt[1] =  mData;
          mCheck = 66+77;
          for(int i=2;i < 30;i++)//data recv and crc calc
          {
             mPkt = Serial.read();
             delay(2);
             mCheck += mPkt;
          }
          mPkt[30] = Serial.read();
          delay(1);
          mPkt[31] = Serial.read();
          Serial.println();
          Serial.print(mCheck);
          Serial.print("  ");
          Serial.println(mPkt[30]*256+mPkt[31]);
          if(mCheck == mPkt[30]*256+mPkt[31])//crc ok
          {
            Serial.println("done33");
            Serial.flush();
            xyz = mPkt[12]*256+mPkt[13];
            return;
          }
        }      
     }
   } 
}

uint8_t draw_state = 0;

void draw(void) {
  u8g_prepare();
  u8g.drawStr(5,5,"pm2.5=");
  u8g.drawStr(90,55,"ug/m3"); 
  switch(9) {
    case 9: u8g_drawxyz();break;
  }
}

void setup(void) {

  // flip screen, if required
  //u8g.setRot180();

  Serial.begin(9600);
  pinMode(13, OUTPUT);           
  digitalWrite(13, HIGH);  
}

void loop(void) {

  // picture loop  
  u8g.firstPage();

  ProcessSerialData(); 
  do {
    draw();
  } while( u8g.nextPage() );

  // increase the state
  draw_state++;
  if ( draw_state >= 9*8 )
    draw_state = 0;

  // rebuild the picture after some delay
  delay(150);

}
