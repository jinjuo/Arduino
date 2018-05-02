

int button = 7;
unsigned long pressTime;
int R = 9;
int G = 8;

void setup() {

pinMode(button,INPUT);
pinMode(R,OUTPUT);
pinMode(G,OUTPUT);
digitalWrite(R,LOW);
digitalWrite(G,LOW);

}

void loop() {
  int state = digitalRead(button);
  if (state == HIGH && (millis()-pressTime)<=1000);
  {
      pressTime = millis();
      changeLight1();
  }
    
  if(state == HIGH && (millis()-pressTime)>1000); 
    {
      pressTime = millis();
      changeLight2();
      }
}  

void changeLight1(){
  digitalWrite(R,HIGH);
  digitalWrite(G,LOW);
  delay(1000);

  delay(5000);
  
  }

void changeLight2(){
  digitalWrite(R,LOW);
  digitalWrite(G,HIGH);
  delay(1000);

  delay(5000);
  
  }


