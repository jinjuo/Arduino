int pins[] = {9,10,11};
int length = sizeof(pins) / sizeof(int);

//想实现呼吸灯效果 需用到支持PWM的引脚
void setup() {

}

void loop() {
  int flag = 0; //渐亮渐暗状态切换
  int sped = 5; //步长
  for (int fadeValue = 0 ; fadeValue <= 255; ) {
      for(int i=0;i<length;i++){
            analogWrite(pins[i], fadeValue); //analogWrite PWM输出0~255
        }
      delay(60);
      if(fadeValue >= 255){
        flag = 1;
       }
       if(fadeValue <= 0){
          flag = 0;
        }
        if(flag == 1){
          fadeValue -= sped;
        }else{
          fadeValue += sped;
        }
  }
}
