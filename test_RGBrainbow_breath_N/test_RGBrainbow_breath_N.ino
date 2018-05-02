void setup() {
  pinMode(9,OUTPUT);//R
  pinMode(10,OUTPUT);//G
  pinMode(11,OUTPUT);//B


}

void loop() {
  int  t = 500;
  RGB(255,0,0);
  delay(t);
  RGB(255,128,0);
  delay(t);
  RGB(255,255,0);
  delay(t);
  RGB(0,255,0);
  delay(t);
  RGB(0,255,255);
  delay(t);
  RGB(0,0,255);
  delay(t);
  RGB(128,0,255);
  delay(t);
 
}


void RGB(int r,int g,int b){
  analogWrite(9,constrain(r,0,255));//写入pwm讯号而不是数字讯号
  analogWrite(10,constrain(g,0,255));
  analogWrite(11,constrain(b,0,255));
  }


  

/* 赤橙黄绿青蓝紫
赤色 【RGB】255, 0, 0 【CMYK】 0, 100, 100, 0 
橙色 【RGB】 255, 165, 0 【CMYK】0, 35, 100, 0 
黄色 【RGB】255, 255, 0 【CMYK】0, 0, 100, 0
绿色  【RGB】0, 255, 0 【CMYK】100, 0, 100, 0 
青色  【RGB】0, 127, 255 【CMYK】100, 50, 0, 0 
蓝色  【RGB】0, 0, 255 【CMYK】100, 100, 0, 0 
紫色  【RGB】139, 0, 255 【CMYK】45, 100, 0, 0
*/

