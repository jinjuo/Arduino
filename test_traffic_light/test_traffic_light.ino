
int lR = 6;
int lY = 8;
int lG = 11;
int t1 = 5000;
int t2 = 2000;

void setup() {
  pinMode(lR, OUTPUT);
  pinMode(lY, OUTPUT);
  pinMode(lG, OUTPUT);
}

void loop() {
  digitalWrite(lR,HIGH);
  digitalWrite(lY,LOW);
  digitalWrite(lG,LOW);
  delay(t1);
  digitalWrite(lR,HIGH);
  digitalWrite(lY,HIGH);
  digitalWrite(lG,LOW);
  delay(t2);
  digitalWrite(lR,LOW);
  digitalWrite(lY,LOW);
  digitalWrite(lG,HIGH);
  delay(t1);
  digitalWrite(lR,LOW);
  digitalWrite(lY,HIGH);
  digitalWrite(lG,LOW);
  delay(t2);
  // put your main code here, to run repeatedly:

}
