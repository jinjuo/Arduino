//项目七作业 – 温度报警器
float sinVal;            
int toneVal;
unsigned long tepTimer ;  


void setup(){ 
    pinMode(8, OUTPUT);        // 蜂鸣器引脚设置
    Serial.begin(9600);        //设置波特率为9600 bps
    pinMode(9, OUTPUT); 
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
}

void loop(){ 
    int val;               // 用于存储LM35读到的值
    double data;          //用于存储已转换的温度值
    val=analogRead(0);   //LM35连到模拟口，并从模拟口读值
    data = (double) val * (5/10.24);  // 得到电压值，通过公式换成温度
     
    if(data<10 & data>35){        //  温度小于10 或者大于35，亮红灯，蜂鸣器发出比较急促的声音 
          for(int x=0; x<180; x++){
            //将sin函数角度转化为弧度
            sinVal = (sin(x*(3.1412/180)));
            //用sin函数值产生声音的频率
            toneVal = 2000+(int(sinVal*1000));
            //给引脚8一个
            tone(8, toneVal);
            delay(2); 
            analogWrite(8,180);
          }
     }   else if (data>=25 & data<=35){    // 温度在25~35之间，亮黄灯，蜂鸣器伴随相对缓和的声音
           for(int x=0; x<180; x++){
            //将sin函数角度转化为弧度
            sinVal = (sin(x*(3.1412/180)));
            //用sin函数值产生声音的频率
            toneVal = 1000+(int(sinVal*1000));
            //给引脚8一个
            tone(8, toneVal);
            delay(10); 
            analogWrite(10,180);
           }
     
    } else if (data>=10 & data<25){    
           noTone(8);          //关闭蜂鸣器 
           analogWrite(9,180);

    } 
 
    
    if(millis() - tepTimer > 500){     // 每500ms，串口输出一次温度值
             tepTimer = millis();
             Serial.print("temperature: ");     // 串口输出“温度”
             Serial.print(data);               // 串口输出温度值
             Serial.println("C");              // 串口输出温度单位
       } 
}

