int buttonPin = 2;
int relayPin = 3;
int relayState = HIGH;
int buttonState;
int lastButtonState = LOW;
long lastDebounceTime = 0;
long debounceDelay = 50;

void setup() {
  pinMode(buttonPin,INPUT);
  pinMode(relayPin,OUTPUT);
  
  digitalWrite(relayPin,relayState);
}

void loop() {
  int reading = digitalRead(buttonPin);
  if(reading != lastButtonState){
      lastDebounceTime = millis();
      }
  if((millis()-lastDebounceTime > debounceDelay)){
    if(reading != buttonState){
       buttonState = reading;
       if(buttonState == HIGH){
          relayState =  !relayState;
      }
    }
  }
digitalWrite(relayPin, relayState);
lastButtonState = reading;
}
