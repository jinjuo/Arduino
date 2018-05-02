//项目一 —— LED 闪烁
/*
   描述：LED每隔一秒交替亮灭一次
*/  

int led = 10;
int ts = 150;
int tl = 400;
int t0 = 100;
int tbr1 = 1000;
int tbr2 = 5000;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  for(int i=0;i<3;i++){
    digitalWrite(led,HIGH);
    delay(ts);
    digitalWrite(led,LOW);
    delay(t0);
    }

    delay(tbr1);

  for(int i=0;i<3;i++){
    digitalWrite(led,HIGH);
    delay(tl);
    digitalWrite(led,LOW);
    delay(t0);
    }

    delay(tbr1);

  for(int i=0;i<3;i++){
    digitalWrite(led,HIGH);
    delay(t0);
    digitalWrite(led,LOW);
    delay(t0);
    }
    
    delay(tbr2);
}




