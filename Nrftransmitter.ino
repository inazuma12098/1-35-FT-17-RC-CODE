/*

這邊的程式碼是搭配Arduino nano寫的，不同的板子腳位功能也可能不同 
請去看完datasheet再測試


*/
#include <nRF24L01.h>
#include <RF24.h>
const byte addr[] = "FT-17";//通道位置5個字元
RF24 RF(9,10);//ce,csn隨便的腳位都可以，若使用原本函式庫的範例是7和8

struct Signal{//跟發射端配對的訊號 可以自己命名想要的
  byte thro;
  byte rudd;  
  byte elev;
  byte aile;
  byte speed1;
  byte trigger;
  };
  
Signal data;  

void Reset(){
  data.thro = 127;//斷線及沒連線時的訊號數字
  data.rudd = 127;
  data.elev = 127;
  data.aile = 127;
  data.speed1 = 127;
  data.trigger = 0;}
  
void setup() {
  Serial.begin(9600);
  RF.begin();                     //開啟無線模組
  RF.setChannel(50);              //設定頻道0~127,頻率＝2400+0~127,有可能超出2.4GHz免許可證頻帶（2.4-2.4835 GHz)，請好好設定不要超出範圍
  RF.openWritingPipe(addr);       //設定通道地址
  RF.setPALevel(RF24_PA_MIN);     //設定功率 RF24_PA_MIN（最小功率) RF24_PA_LOW（低功率）RF24_PA_HIGH（高功率）RF24_PA_MAX（最大功率）
  RF.setDataRate(RF24_250KBPS);   //設定速率 250KBPS、1MBPS、2MBPS
  RF.stopListening();//停止接收改發射
  Reset();
}    

int value(int channel,int low,int mid, int high,bool reverse){
  channel=constrain(channel,low,high);
  if(channel<mid){ 
    channel=map(channel,low,mid,0,128);   //小於mid，值輸出0~128
    }
  else {
        channel=map(channel,mid,high,128,255); //大於mid，值輸出128~255
        }
  return(reverse ? 255-channel:channel);  //用reverse判斷正反方向(例如原本搖桿網上是後退，改變true或false就可以變成向上是前進)
  }

  
void loop() {
  
    data.thro = value(analogRead(A0),0,512,1023,false);//這邊訊號是讀取可變電阻上的電壓，原本是0~1023，用了副程式把它轉換成0~255
    data.rudd = value(analogRead(A1),0,512,1023,true); //analogRead只有在A0~A7腳位上
    data.elev = value(analogRead(A2),0,512,1023,true);
    data.aile = value(analogRead(A3),0,512,1023,true);
    data.speed1= digitalRead(2);//這邊訊號是讀取電阻上的電壓，0或1(LOW或HIGH)
    data.trigger=digitalRead(5);
    
    RF.write(&data,sizeof(Signal)); //發射訊號
                                                                                                                        
}
