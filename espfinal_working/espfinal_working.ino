#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
//#define bat 0
#define tmp 0
#define hmd 1
String apiKey = "L22QTULTOGQ1RUQN";     //  Enter your Write API key from ThingSpeak
const char *ssid =  "sj";     // replace with your wifi ssid and wpa2 key
const char *pass =  "sachinjadhav";
const char* server = "api.thingspeak.com";
WiFiClient client;
String sen1;
byte data[7]="";
byte tmp1,tmp2,tmp3,tmp4;
byte hmd1,hmd2,hmd3,hmd4;
 byte d1=0,d2=0,d3=0,d4=0;///flags for data check
void http_request();
HardwareSerial Serial2(2);
void setup()
{
  Serial.begin(115200);
  Serial2.begin(2400,SERIAL_8N1,16,17);// 16 RX 17 Tx
  Serial.println("Connecting to ");
       Serial.println(ssid);
       WiFi.begin(ssid, pass);
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
       
}


void loop() 
{
 
   byte z=0;
   byte i=0;
    //Serial2.begin(2400,SERIAL_8N1,16,17);// 16 RX 17 Tx
    //for handshaking
     Serial2.write('C'); 
     //wait for data available send by arduino 
     delay(4000);
    while(Serial2.available()&&((z!=1)|(z!=2)|(z!=3)|(z!=4)))
      {
        //Serial.print("got data");
         z = Serial2.read();
       if (z!=' ')
        {
          data[i] = z;
          i++; 
         }
       Serial.println(z);
     }
     // update data according to fields
     if (z==1)
      { tmp1 = data[tmp];
        hmd1 = data[hmd];
        d1=1;
       }
        if (z==2)
      { tmp2 = data[tmp];
        hmd2 = data[hmd];
        d2=1;
      }
         if (z==3)
      { tmp3 = data[tmp];
        hmd3 = data[hmd];
        d3=1;
       }
         if (z==4)
      { tmp4 = data[tmp];
        hmd4 = data[hmd];
        d4=1;
       }
      //Seril.println(sen1);
        http_request();
      
       //ESP in sleep
   /*    if(d1&&d2&&d3&&d4)
       {
         Serial.print("SLE");
         //just for handshaking
        //Serial2.write('D');
        esp_sleep_enable_ext0_wakeup(GPIO_NUM_33,1); //1 = High, 0 = Low
        esp_deep_sleep_start();
       }
     */ 
 // Serial2.write(z);
//    delay(100);
//    while(Serial2.available())
//    {
//    esp_deep_sleep_start();
//    Serial.print("insleep");
//    }
 
}
/// post request to send data on Thingspeak (Internet)
void http_request()
{
     if (client.connect(server,80))  
      {
         String postStr = apiKey;
         postStr +="&field1=";
         postStr +=tmp1;
         postStr +="&field2=";
         postStr +=hmd1;
         postStr +="&field3=";
         postStr +=tmp2;
         postStr +="&field4=";
         postStr +=hmd2;
         postStr +="&field5=";
         postStr +=tmp3;
         postStr +="&field6=";
         postStr +=hmd3;
         postStr +="&field7=";
         postStr +=tmp4;
         postStr +="&field8=";
         postStr +=hmd4;
         postStr += "\r\n\r\n";
           client.print("POST /update HTTP/1.1\n");
           client.print("Host: api.thingspeak.com\n");
           client.print("Connection: close\n");
           client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
           client.print("Content-Type: application/x-www-form-urlencoded\n");
           client.print("Content-Length: ");
           client.print(postStr.length());
           client.print("\n\n");
           client.print(postStr); 
      }
      client.stop();
      delay(15000);
}


