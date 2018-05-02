
unsigned char state = 0;

void setup() {
    pinMode(13,OUTPUT);
    pinMode(3,INPUT);
    attachInterrupt(1,blink,RISING);

}

void loop() {
    if(state!=0){
      state = 0;
      digitalWrite(13,HIGH);
      delay(500);
      }
      else{
        digitalWrite(13,LOW);
        }
}

void blink(){
  state++;
  }
