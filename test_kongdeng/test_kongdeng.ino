
int redPin = 9;
int greenPin = 10;
int bluePin = 11;


void setup() {
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  Serial.begin(9600);

}

void loop() {
  int potRed = analogRead(0);
  int potGreen = analogRead(1);
  int potBlue = analogRead(2);

  int val1 = map(potRed,1,1023,0,255);
  int val2 = map(potGreen,1,1023,0,255);
  int val3 = map(potBlue,1,1023,0,255);


  Serial.print("Red:");
  Serial.print(val1);
  Serial.print("Green:");
  Serial.print(val2);
  Serial.print("Blue:");
  Serial.println(val3);
 
   colorRGB(val1,val2,val3);      // 让RGB LED 呈现对应颜色
}

//该函数用于显示颜色
void colorRGB(int red, int green, int blue){     
   analogWrite(redPin,constrain(red,0,255));
   analogWrite(greenPin,constrain(green,0,255));
   analogWrite(bluePin,constrain(blue,0,255));
}


