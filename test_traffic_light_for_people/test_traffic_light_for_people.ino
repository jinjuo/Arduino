
int carR = 12;
int carY = 11;
int carG = 10;
int button = 9;
int pepR = 8;
int pepG = 7;
int crossTime = 5000;
unsigned long changeTime;

void setup() {
  pinMode(carR,OUTPUT);
  pinMode(carY,OUTPUT);
  pinMode(carG,OUTPUT);
  pinMode(pepR,OUTPUT);
  pinMode(pepG,OUTPUT);
  pinMode(button,INPUT);
  digitalWrite(carG,HIGH);
  digitalWrite(pepR,HIGH);
  }

void loop() {
  int state = digitalRead(button);
  if(state == HIGH && (millis()-changeTime) > 5000){
  changeLight();
    }
}
void changeLight(){
  //车黄灯2秒,车绿灯灭,行人不变
  digitalWrite(carG,LOW);
  digitalWrite(carY,HIGH);
  delay(2000);
  //车黄灯灭,红灯亮,行人不变,等待1s的安全时间
  digitalWrite(carY,LOW);
  digitalWrite(carR,HIGH);
    delay(1000);
  
  // 行人绿灯亮,红灯灭;持续5s
  digitalWrite(pepG,HIGH);
  digitalWrite(pepR,LOW);
  delay(crossTime);
  //车不变,行人绿灯闪烁10次
     for(int x=0;x<10;x++){
       digitalWrite(pepG,HIGH);
        delay(250);
        digitalWrite(pepG,LOW);
       delay(250);
       }

  //车黄灯亮,行人绿灯灭,红灯亮;持续2s
  digitalWrite(carY,HIGH);
  digitalWrite(pepG,LOW);
  digitalWrite(pepR,HIGH);
  delay(2000);

  //记录时间,结束loop
  changeTime = millis();
  }
  
  // put your main code here, to run repeatedly:

