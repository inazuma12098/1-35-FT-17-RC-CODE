/*

這邊的程式碼是搭配Arduino nano寫的，不同的板子腳位功能也可能不同 
請去看完datasheet再測試


*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
const byte addr[] = "FT-17";//通道位置5個字元
const byte pipe = 1;  // 通道編號有0~5
RF24 RF(2,3);//名字(ce,csn) 隨便的腳位都可以，若使用原本函式庫的範例是7和8

struct Signal{//跟發射端配對的訊號 可以自己命名想要的
  byte thro;
  byte rudd;
  byte elev;
  byte aile;
  byte speed1;
  byte trigger;
  };
  
Signal data;  

int signal1,signal2,signal3,signal4,signal5,signal6;

void Reset()
  {
  data.thro = 127;//斷線及沒連線時的訊號數字
  data.rudd = 127;
  data.elev = 127;
  data.aile = 127;
  data.speed1 = 127;
  data.trigger = 0;}
   
void setup() {
  Serial.begin(9600);
  
  Reset();                        //重置
  RF.begin();                     //開啟無線模組
  RF.setChannel(50);              //設定頻道0~127,頻率＝2400+0~127,有可能超出2.4GHz免許可證頻帶（2.4-2.4835 GHz)，請好好設定不要超出範圍
  RF.openReadingPipe(pipe,addr);  //設定通道地址
  RF.setPALevel(RF24_PA_MIN);     //設定功率 RF24_PA_MIN（最小功率) RF24_PA_LOW（低功率）RF24_PA_HIGH（高功率）RF24_PA_MAX（最大功率）
  RF.setDataRate(RF24_250KBPS);   //設定速率 250KBPS、1MBPS、2MBPS
  RF.startListening();            //開始接收
}
unsigned long lastreceive = 0;   //宣告一個時間變數

void startreceive()                   //讀取訊號用的副程式
  {
    while ( RF.available() ) 
    {
    RF.read(&data, sizeof(Signal));//接收
    lastreceive = millis();   
    }
  }
  
  void loop() {
    startreceive();//接收訊號
   
    unsigned long now = millis();
    
    if ( now - lastreceive > 1000 )      // 超過一定時間沒訊號就回到重置的動作上(斷訊保護)
    {    
    Reset();                              
    }
    
    signal1=map(data.thro,0,255,500,2500);//把原本發射端訊號值0~255放大為500~2500，中立點大約是1496
    signal2=map(data.rudd,0,255,500,2500);
    signal3=map(data.elev,0,255,500,2500);
    signal4=map(data.aile,0,255,500,2500);
    signal5=data.speed1;                  //照發射端的值
    signal6=data.trigger;                 //照發射端的值
    
    //在監控視窗顯示值
    Serial.println(String("")+"訊號1 = "+ signal1+" 訊號2 = "+ signal2+" 訊號3 = "+ signal3+" 訊號4 = "+ signal4+" 訊號5 = "+ signal5+" 訊號6 = "+ signal6 );
  
   
  
  }
