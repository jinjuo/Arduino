int led = 10;


void setup() {
pinMode(led,OUTPUT);
}

void loop() {
  fadeON(1000,5);
  fadeOff(1000,5);

}
void fadeON(unsigned int time, int a){
    for(int value = 0;value<255;value+= a){
      analogWrite(led,value);
      delay(time*a/255);
      }
  }

void fadeOff(unsigned int time,int b){
  for(int value =255;value>0;value-=b){
     analogWrite(led,value);
     delay(time*b/255);
   }

}  

