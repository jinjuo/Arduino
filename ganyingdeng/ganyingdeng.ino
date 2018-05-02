int led =13;
int val = 0;

void setup() {
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(0);
  Serial.println(val);
  if(var<1000){
       digitalWrite(led,LOW);
  }else{
       digitalWrite(led,HIGH);
  }
  delay(10);
}
