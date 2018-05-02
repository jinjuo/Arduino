/*这个程序叫做迈泰调制机器人
  
* 主要功能就是调制玛歌迈泰
  
* 作者是Ted Kinsman Rochester Institute of Technology
  
*March 2017 [url=mailto:emkpph@rit.edu]emkpph@rit.edu[/url]
  
*12v直流马达[color=#333333][size=13px]泵[/size][/color]打出1盎司的液体需要32秒
  
*/
  
#define Rum 1 // (1号[color=#333333][size=13px]泵[/size][/color])12VDC马达连接1号脚位，打入兰姆酒
  
#define LED8 8 // (1号[color=#333333][size=13px]泵[/size][/color])LED显示兰姆酒打入状况
  
  
#define Curacao 2 // (2号[color=#333333][size=13px]泵[/size][/color]) 柑香酒连接 2号脚位
  
#define LED9 9 // (2号[color=#333333][size=13px]泵[/size][/color])LED显示柑香酒打入状况
  
  
#define Orgeat 3 // (3号[color=#333333][size=13px]泵[/size][/color])连接 3号脚位
  
#define LED10 10 // 3号[color=#333333][size=13px]泵[/size][/color]上的LED连接到10号脚位
  
  
#define Grenedine 4 // (4号[color=#333333][size=13px]泵[/size][/color])连接 4号脚位
  
#define LED11 11 // 4号[color=#333333][size=13px]泵[/size][/color]上的LED连接到11号脚位
  
#define PineLime 5 // 5号[color=#333333][size=13px]泵[/size][/color]连接菠萝与莱姆汁
  
#define LED12 12 // 5号[color=#333333][size=13px]泵[/size][/color]上的LED连接到12号脚位
  
#define doorbell 13 // 用门铃启动开关
  
#define pump6 6 // 6号脚位连接大型潜入式[color=#333333][size=13px]泵[/size][/color]
  
  
int strobe=100; // 控制LED闪烁速度
  
int sensorPin = A0; // 模拟读取：用来侦测是否有按压门铃开关
  
int sensorValue = 0;  // 如果读取到门铃值，会写入这里
  
  
void setup()
  
{
  
pinMode(Rum, OUTPUT);
  
pinMode(LED8, OUTPUT);
  
pinMode(Curacao, OUTPUT);
  
pinMode(LED9, OUTPUT);
  
pinMode(Orgeat, OUTPUT);
  
pinMode(LED10, OUTPUT);
  
pinMode(Grenedine, OUTPUT);
  
pinMode(LED11, OUTPUT);
  
pinMode(LED12, OUTPUT);
  
pinMode(doorbell, INPUT);
  
pinMode(pump6, OUTPUT);
  
digitalWrite (LED8, LOW); // 1号LED亮
  
digitalWrite (Rum, HIGH); // 关闭1号[color=#333333][size=13px]泵[/size][/color]
  
digitalWrite (LED9, LOW);
  
digitalWrite (Curacao, HIGH); // 关闭3号[color=#333333][size=13px]泵[/size][/color]
  
digitalWrite (LED10, LOW);
  
digitalWrite (Orgeat, HIGH); // 关闭3号[color=#333333][size=13px]泵[/size][/color]
  
digitalWrite (LED11, LOW); // 关闭4号[color=#333333][size=13px]泵[/size][/color]
  
digitalWrite (PineLime, HIGH); // 关闭4号[color=#333333][size=13px]泵[/size][/color]
  
digitalWrite (LED11, LOW);
  
digitalWrite (Grenedine, HIGH);// 关闭5号[color=#333333][size=13px]泵[/size][/color]
  
digitalWrite (pump6, HIGH);// 关闭6号[color=#333333][size=13px]泵[/size][/color]
  
delay(1000); // 让继电器在开始运行前准备就绪
  
}
  
void loop()   // 这部分的程序代码会持续循环
  
{
  
sensorValue = analogRead(sensorPin);
  
// 这个部分是在让LED闪闪发亮，这样机器人看起来会比较酷
  
// 闪灯在按下开始钮的时候会停止
  
// 按下按钮时，LED会显示在运转的马达
  
digitalWrite (LED8, HIGH); // 开启8号脚位的LED
  
delay(strobe);         // 控制LED闪烁速度
  
digitalWrite (LED8, LOW); // 关闭8号脚位的LED
  
delay(strobe);
  
digitalWrite (LED9, HIGH); // 开启9号脚位的LED
  
delay(strobe);
  
digitalWrite (LED9, LOW); // 关闭9号脚位的LED
  
delay(strobe);
  
digitalWrite (LED10, HIGH); // 开启10号脚位的LED
  
delay(strobe);
  
digitalWrite (LED10, LOW); // 关闭10号脚位的LED
  
delay(strobe);
  
digitalWrite (LED11, HIGH); // 开启11号脚位的LED
  
delay(strobe);
  
digitalWrite (LED11, LOW); // 关闭11号脚位的LED
  
delay(strobe);
  
digitalWrite (LED12, HIGH); // 开启12号脚位的LED
  
delay(strobe);
  
digitalWrite (LED12, LOW); // 关闭12号脚位的LED
  
delay(strobe);
  
sensorValue = analogRead(sensorPin);
  
if(sensorValue < 300){
  
digitalWrite (LED8, HIGH); // 1号LED开启
  
digitalWrite (Rum, LOW); // 1号[color=#333333][size=13px]泵[/size][/color]开启
  
digitalWrite (LED9, HIGH);
  
digitalWrite (Curacao, LOW); // 2号[color=#333333][size=13px]泵[/size][/color]开启
  
digitalWrite (LED10, HIGH);
  
digitalWrite (Orgeat, LOW); // 3号[color=#333333][size=13px]泵[/size][/color]开启
  
digitalWrite (LED11, HIGH);
  
digitalWrite (Grenedine, LOW);// 4号[color=#333333][size=13px]泵[/size][/color]开启
  
delay(8000);       // 等待8秒钟打出1/4盎司液体
  
digitalWrite (LED10, LOW); // 关闭杏仁糖浆LED P3
  
digitalWrite (Orgeat, HIGH);   // 关闭杏仁糖浆[color=#333333][size=13px]泵[/size][/color] P3
  
digitalWrite (LED11, LOW);   // 5号[color=#333333][size=13px]泵[/size][/color]LED关闭
  
digitalWrite (Grenedine, HIGH); // 4号[color=#333333][size=13px]泵[/size][/color]关闭
  
delay(8000);     // 等待8秒钟打出1/4盎司液体
  
digitalWrite (Curacao, HIGH);   // 关闭柑香酒[color=#333333][size=13px]泵[/size][/color] 2号
  
digitalWrite (LED9, LOW); // 关闭柑香酒LED 2号
  
// 这个时候，柑香酒开关开启共16秒，送出1/2盎司。
  
delay(16000);   // 等待8秒钟打出1/4盎司液体
  
digitalWrite (LED8, LOW); // 关闭1号[color=#333333][size=13px]泵[/size][/color] LED
  
digitalWrite (Rum, HIGH);   // 关闭1号[color=#333333][size=13px]泵[/size][/color]（兰姆酒）
  
digitalWrite (pump6, LOW);   // 开启菠萝汁[color=#333333][size=13px]泵[/size][/color]（6号[color=#333333][size=13px]泵[/size][/color]）
  
//digitalWrite (PineLime, LOW); // low 打开继电器，打开[color=#333333][size=13px]泵[/size][/color]
  
delay(2500); // 延迟4秒，送出菠萝汁。
  
digitalWrite (pump6, HIGH);     // 关闭菠萝汁[color=#333333][size=13px]泵[/size][/color]（6号[color=#333333][size=13px]泵[/size][/color]）
  
//digitalWrite (PineLime, HIGH); // 关闭菠萝汁继电器
  
}
  
}
