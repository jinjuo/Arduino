
void setup() {
pinMode(9,OUTPUT);//红灯
pinMode(10,OUTPUT);//黄灯2
pinMode(11,OUTPUT);//黄灯2
}

void loop(){
  int a = random(0,120);
  int b = random(0,150);
  int c = random(0,150);
  int valueR = a+135;
  int valueY = b+115;
  int valueY2 = c+50;
  analogWrite(9,valueR);
  delay(100);
  analogWrite(10,valueY);
  delay(100);
  analogWrite(10,valueY2);
  delay(100);
  
  }


