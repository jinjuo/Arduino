//项目四 – 呼吸灯
int ledPin = 10;

void setup() {
      pinMode(ledPin,OUTPUT);
     // Serial.begin(9600);
}

void loop(){
      fadeOn(1500,5);
      fadeOff(1500,5);
}

void fadeOn(unsigned int time,int increament){
	for (int value = 0 ; value < 255; value+=increament){ 
	        Serial.println(value);
		analogWrite(ledPin, value);
		delay(time/(255/increament));
        } 
}

void fadeOff(unsigned int time,int decreament){
	for (int value = 255; value >0; value-=decreament){ 
	   //     Serial.println(value);
		analogWrite(ledPin, value); 
		delay(time/(255/decreament)); 
	}
}
