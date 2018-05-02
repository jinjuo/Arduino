# include <Servo.h>
Servo myservo;
int in = 0;
int val;


void setup() {
    myservo.attach(9);    
}

void loop() {
    val = analogRead(in);
    val = map(val,0,1023,0,179);
    myservo.write(val);
    delay(15);
}
