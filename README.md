
<br>這是利用Arduino和nRF24L01無線模組所做的遙控程式碼
<br>改變參數就能做到其他遙控的功能
<br>也能夠自己增加開關搖桿等等

<br>發射端的電路我是以可變電阻(joystick,搖桿)接在A0、A1、A2、A3等等腳位來讀取電位(analogRead,0~1023,A系列腳位都能用這個函式)
<br>其他撥桿(switch)接在D2、D5，用digitalRead讀LOW或HIGH
<br>依照值的不同發出不同的值。腳位的編號在程式碼中都有寫
<br>nRF24L01的MISO連nano的D12(MISO)
<br>MOSI連nano的D11(MOSI)
<br>SCK連nano的D13(SCK)
<br>CE連D9(自訂)
<br>CSN連D10(自訂)
<br><a style="color:RED ">nRF24L01用的是3.3Ｖ</a>
<br>
使用這個程式碼之前請先安裝這個函式庫喔 
<br>
<a href="https://github.com/nRF24/RF24 " target = "_blank">RF24</a>
<br><br>
程式碼可以在下面的連結複製
<br>
<br>
<a href="transmitter code.html" target ="_blank">transmitter code 發射端簡易程式碼(網頁瀏覽)</a>沒有OLED的部分
<br>
<a href="receiver code.html" target ="_blank">receiver code 接收端簡易程式碼(網頁瀏覽)</a> 只有在monitor顯示數值
