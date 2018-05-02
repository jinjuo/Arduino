void setup() {
  pinMode(9,OUTPUT);//R
  pinMode(10,OUTPUT);//G
  pinMode(11,OUTPUT);//B

}

void loop() {
  RGB(random(0,255),random(0,255),random(0,255));
  delay(1000);
}

void RGB(int r, int g, int b){
  analogWrite(9,constrain(r,0,255));//写入pwm讯号而不是数字讯号
  analogWrite(10,constrain(g,0,255));
  analogWrite(11,constrain(b,0,255));
  
  }
