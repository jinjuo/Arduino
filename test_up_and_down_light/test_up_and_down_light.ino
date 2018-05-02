int n = 100;
void setup() {
  pinMode(4,INPUT);
  pinMode(6,OUTPUT);//灯
  pinMode(10,INPUT);
  
}

void loop() {
  int up = digitalRead(4);//读取按键
  int down = digitalRead(10);
  if(up == HIGH){
    n = n+10;
//    constrain(n,0,255); // 用constrain函数可能也可以
    if(n>=255){  //防止数字过大
      n = 255;
      }
    }
  analogWrite(6,n);//模拟端口数据写入
  delay(100);//防止连按的错误

   if(down == HIGH){
    n = n-10;
    if(n<=0){ //防止数字太小
      n =0;
      }
    }
  analogWrite(6,n);
  delay(100);

}
