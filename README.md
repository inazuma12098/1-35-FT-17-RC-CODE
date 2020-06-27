
<br>這是利用Arduino和nRF24L01無線模組所做的遙控程式碼
<br>改變參數就能做到其他遙控的功能
<br>也能夠自己增加開關搖桿等等

<br>發射端的電路我是以可變電阻接在A0、A1等等腳位來讀取電位(analogRead)
<br>依照值的不同發出不同的值。腳位的編號在程式碼中都有寫
<br>nRF24L01的MISO連nano的D12
<br>MOSI連nano的D11
<br>SCK連nano的D13
<br>
<br>
使用這個程式碼之前請先安中這個函式庫喔 
<br>
<a href="https://github.com/nRF24/RF24 " target = "blank">RF24</a>
<br><br>
程式碼可以在下面的連結複製
<br>
<br>
<a href="transmitter code.html" target ="blank">發射端簡易程式碼(網頁瀏覽)</a>
<br>
<a href="receiver code.html" target ="blank">接收端簡易程式碼(網頁瀏覽)</a> 只有在監控視窗顯示數值