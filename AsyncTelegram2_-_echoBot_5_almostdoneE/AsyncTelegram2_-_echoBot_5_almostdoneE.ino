
/*
Flow     : 1. Built-in LED akan berkedip terus menerus dengan interval 150 ms
              2. Bersamaan dengan itu, cek apakah ada pesan yang diterima. Kirim
                 kembali pesan yang sama ketika ada pesan yang diterima.

Intruction to install :
1. Install Arduino 1.8.16
2. Install Board ESP8266 Versi 3.0.0 , file_> preference->copy package
http://arduino.esp8266.com/stable/package_esp8266com_index.json
3. Install libraries di Manage libraries -> AsyncTelegram 2 (2.0.8) Tolentino Cotesta
4. Install libraries  SSLClient (1.6.11) OPEnS Lab
5. Install libraries  ArduinoJson (6.19.2)     Benoit Blanchon

*/

#define USE_CLIENTSSL true

#include <AsyncTelegram2.h>
#include <SoftwareSerial.h>
#define RX_S 4  //D2
#define TX_S 5  //D1


// Timezone definition
#include <time.h>
//#define MYTZ "CET-1CEST,M3.5.0,M10.5.0/3"
#define MYTZ "WIB-7"

// Jika board yang digunakan ESP8266 maka library yang digunakan
// adalah #include <ESP8266WiFi.h> -> sudah ada di core esp8266
#ifdef ESP8266
#include <ESP8266WiFi.h>
BearSSL::WiFiClientSecure client;
BearSSL::Session   session;
BearSSL::X509List  certificate(telegram_cert);

// Jika board yang digunakan  ESP32 maka library yang diginakan
// adalah #include <WiFi.h>, #include <WiFiClient.h> -> sudah ada di core esp32
// dan #include <SSLClient.h> -> perlu di download
// serta #include <WiFiClientSecure.h> -> sudah ada di core esp32
#elif defined(ESP32)
#include <WiFi.h>
#include <WiFiClient.h>
#if USE_CLIENTSSL
#include <SSLClient.h>
#include "tg_certificate.h"
WiFiClient base_client;
SSLClient client(base_client, TAs, (size_t)TAs_NUM, A0, 1, SSLClient::SSL_ERROR);
#else
#include <WiFiClientSecure.h>
WiFiClientSecure client;
#endif
#endif

// Buat object myBot
AsyncTelegram2 myBot(client);

SoftwareSerial sserial = SoftwareSerial(RX_S,TX_S);

// SSID dan Password WIFI
const char* ssid  =  "MKCHECK";     // SSID WiFi network
const char* pass  =  "12344321";     // Password  WiFi network

// Token Telegram yang diperoleh ketika membuat BOT lewat BotFather
const char* token =  "7190192639:AAGOV0xjya-a2pnsCKCcpQxgYr2VRnQ0vlg";  // Telegram token
//int64_t userid = -4175257531; //id grup

String data;
char c;

//String STATUS="";
String MK1O="";
String MK1C="";
String MK2O="";
String MK2C="";
String MK3O="";
String MK3C="";
String MK4O="";
String MK4C="";
String MK5O="";
String MK5C="";
String MK6O="";
String MK6C="";
String MK7O="";
String MK7C="";
String MK8O="";
String MK8C="";
String MK9O="";
String MK9C="";
String MK10O="";
String MK10C="";
String MK11O="";
String MK11C="";
String MK12O="";
String MK12C="";
String MK13O="";
String MK13C="";
String MK14O="";
String MK14C="";
String MK15O="";
String MK15C="";
String MK16O="";
String MK16C="";
String message ;


void setup() {
  // Set LED_BUILTIN sebagai output
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RX_S,INPUT);
  pinMode(TX_S,OUTPUT);
  // inisialisasi serial
  Serial.begin(115200);
  sserial.begin(9600);
  Serial.print("\nDemo Using Library AsyncTelegram2 on ");
 
#ifdef ESP8266
  Serial.println("ESP8266");
#elif defined(ESP32)
  Serial.println("ESP32");
#endif

  Serial.println("\nStarting TelegramBot...");
  // Konek ke Hotspot
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  delay(500);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }

#ifdef ESP8266
  // Sinkronisasi waktu dengan NTP untuk sertifikat Telegram
  configTime(MYTZ, "time.google.com", "time.windows.com", "pool.ntp.org");
  // Set certficate, session and some other base client properties
  client.setSession(&session);
  client.setTrustAnchors(&certificate);
  client.setBufferSizes(1024, 1024);
#elif defined(ESP32)
  // Sinkronisasi waktu dengan NTP
  configTzTime(MYTZ, "time.google.com", "time.windows.com", "pool.ntp.org");
#if USE_CLIENTSSL == false
  client.setCACert(telegram_cert);
#endif
#endif

  // Setting properti bot telegram
  myBot.setUpdateTime(2000);
  myBot.setTelegramToken(token);

  // Cek apakah sudah tersambung dengan server telegram
  Serial.print("\nTest Telegram connection... ");
  myBot.begin() ? Serial.println("OK") : Serial.println("NOK");

  // Pesan selamat datang
  char welcome_msg[128];
  snprintf(welcome_msg, 128, "BOT @%s online using AsyncTelegram2", myBot.getBotName());

  // Kirim pesan selamat datang ke user telegram
  // user id yang bisa dicek di akun userID pada aplikasi telegram
  int64_t userid = 5696629558;
  //int64_t userid = -4175257531; //id grup
  //-> token -> 7190192639:AAGOV0xjya-a2pnsCKCcpQxgYr2VRnQ0vlg
  
  myBot.sendTo(userid, welcome_msg);
}


int64_t userid = -4128298459; //id grup
void loop()
{
  // LED Built-in akan berkedip dengan interval 150ms
  static uint32_t ledTime = millis();
  if (millis() - ledTime > 150) {
    ledTime = millis();
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }

  // variabel lokal untuk menyimpan data pesan telegram
  TBMessage msg;
  //msg.chatId=userid;

  // Ketika ada pesan masuk, tulis di serial monitor dan
  // balas pesan yang sama ke pengirim pesan
  if (myBot.getNewMessage(msg)) {
    // Send a message to your public channel
    String message,wadah ;
    message += "Message from @";
    message += myBot.getBotName();
    message += ":\n";
    message += msg.text;
    
    Serial.println(message);
    myBot.sendMessage(msg, msg.text);
    if (msg.text.equalsIgnoreCase("TEST")) {              
      myBot.sendMessage(msg,"Hello there");  //kirim pesan ke bot telegram
    }
  }

  while(sserial.available()>0){
    delay(10);
    c = sserial.read();
    data += c;
    Serial.print("single=");
    Serial.print(data);
    Serial.print("= ");
  }
  Serial.print("GABUNG= ");
    Serial.print(data);
    Serial.print("----- By Slot= ");
    char first=data.charAt(0);
    char second=data.charAt(1);
    char third=data.charAt(2);
    char forth=data.charAt(3);
    Serial.print(first);
    Serial.print(" ");
    Serial.print(second);
    Serial.print(" ");
    Serial.print(third);
    Serial.print(" ");
    Serial.print(forth);
    Serial.println(" ");


    if (data.length()>0) {
    //myBot.sendMessage(msg, " tamat");
    delay(10);
    data = "";
  }

//-----------------MK 1------------
    if(first=='1' && second=='O' && third=='C'){
      Serial.println("MK_1-NO_1 Closed");    
      //myBot.sendTo(userid, "MK_1-NO_1 Closed");
      myBot.sendTo(5696629558, "MK_1-NO_1 Closed");
      delay(100);
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK1O="MK_1-NO_1 Closed";
    }
        
    if(first=='1' && second=='O' && third=='O'){
      Serial.println("MK_1-NO_1 Opened");
      myBot.sendTo(userid,"MK_1-NO_1 Opened");
      myBot.sendTo(5696629558, "MK_1-NO_1 Opened");

      //delay(100);
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK1O="MK_1-NO_1 Opened";
    }

      if(first=='1' && second=='C' && third=='C'){
      Serial.println("MK_1-NC_1 Closed");
      myBot.sendTo(userid,"MK_1-NC_1 Closed");
      //delay(500);
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK1C="MK_1-NC_1 Closed";
    }
        
    if(first=='1' && second=='C' && third=='O'){
      Serial.println("MK_1-NC_1 Opened");
      myBot.sendTo(userid,"MK_1-NC_1 Opened");
      //delay(500);
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK1C="MK_1-NC_1 Opened";
    }
///////////------



//-----------------MK 2------------
if(first=='2' && second=='O' && third=='C'){
      Serial.println("MK_2-NO_1 Closed");
     myBot.sendTo(userid, "MK_2-NO_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK2O="MK_2-NO_1 Closed";
    }
        
    if(first=='2' && second=='O' && third=='O'){
      Serial.println("MK_2-NO_1 Opened");
      myBot.sendTo(userid, "MK_2-NO_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK2O="MK_2-NO_1 Opened";
    }

      if(first=='2' && second=='C' && third=='C'){
      Serial.println("MK_2-NC_1 Closed");
      myBot.sendTo(userid, "MK_2-NC_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK2C="MK_2-NC_1 Closed";
    }
        
    if(first=='2' && second=='C' && third=='O'){
      Serial.println("MK_2-NC_1 Opened");
      myBot.sendTo(userid, "MK_2-NC_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK2C="MK_2-NC_1 Opened";
    }  
//---

//-----------------MK 3------------
if(first=='3' && second=='O' && third=='C'){
      Serial.println("MK_3-NO_1 Closed");
     myBot.sendTo(userid, "MK_3-NO_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK3O="MK_3-NO_1 Closed";
    }
        
    if(first=='3' && second=='O' && third=='O'){
      Serial.println("MK_3-NO_1 Opened");
     myBot.sendTo(userid, "MK_3-NO_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK3O="MK_3-NO_1 Opened";
    }

      if(first=='3' && second=='C' && third=='C'){
      Serial.println("MK_3-NC_1 Closed");
      myBot.sendTo(userid, "MK_3-NC_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK3C="MK_3-NC_1 Closed";
    }
        
    if(first=='3' && second=='C' && third=='O'){
      Serial.println("MK_3-NC_1 Opened");
      myBot.sendTo(userid, "MK_3-NC_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK3C="MK_3-NC_1 Opened";
    }  
//---

//-----------------MK 4------------
if(first=='4' && second=='O' && third=='C'){
      Serial.println("MK_4-NO_1 Closed");
      myBot.sendTo(userid, "MK_4-NO_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK4O="MK_4-NO_1 Closed";
    }
        
    if(first=='4' && second=='O' && third=='O'){
      Serial.println("MK_4-NO_1 Opened");
      myBot.sendTo(userid, "MK_4-NO_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK4O="MK_4-NO_1 Opened";
    }

      if(first=='4' && second=='C' && third=='C'){
      Serial.println("MK_4-NC_1 Closed");
      myBot.sendTo(userid, "MK_4-NC_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK4C="MK_4-NC_1 Closed";
    }
        
    if(first=='4' && second=='C' && third=='O'){
      Serial.println("MK_4-NC_1 Opened");
     myBot.sendTo(userid, "MK_4-NC_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK4C="MK_4-NC_1 Opened";
    }  
//---

//-----------------MK 5------------
if(first=='5' && second=='O' && third=='C'){
      Serial.println("MK_5-NO_1 Closed");
     myBot.sendTo(userid, "MK_5-NO_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK5O="MK_5-NO_1 Closed";
    }
        
    if(first=='5' && second=='O' && third=='O'){
      Serial.println("MK_5-NO_1 Opened");
     myBot.sendTo(userid, "MK_5-NO_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK5O="MK_5-NO_1 Opened";
    }

      if(first=='5' && second=='C' && third=='C'){
      Serial.println("MK_5-NC_1 Closed");
     myBot.sendTo(userid, "MK_5-NC_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK5C="MK_5-NC_1 Closed";
    }
        
    if(first=='5' && second=='C' && third=='O'){
      Serial.println("MK_5-NC_1 Opened");
     myBot.sendTo(userid, "MK_5-NC_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK5C="MK_5-NC_1 Opened";
    }  
//---


//-----------------MK 6------------
if(first=='6' && second=='O' && third=='C'){
      Serial.println("MK_6-NO_1 Closed");
     myBot.sendTo(userid, "MK_6-NO_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK6O="MK_6-NO_1 Closed";
    }
        
    if(first=='6' && second=='O' && third=='O'){
      Serial.println("MK_6-NO_1 Opened");
     myBot.sendTo(userid, "MK_6-NO_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK6O="MK_6-NO_1 Opened";
    }

      if(first=='6' && second=='C' && third=='C'){
      Serial.println("MK_6-NC_1 Closed");
     myBot.sendTo(userid, "MK_6-NC_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK6C="MK_6-NC_1 Closed";
    }
        
    if(first=='6' && second=='C' && third=='O'){
      Serial.println("MK_6-NC_1 Opened");
     myBot.sendTo(userid, "MK_6-NC_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK6C="MK_6-NC_1 Opened";
    }  
//---

//-----------------MK 7------------
if(first=='7' && second=='O' && third=='C'){
      Serial.println("MK_7-NO_1 Closed");
     myBot.sendTo(userid, "MK_7-NO_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK7O="MK_7-NO_1 Closed";
    }
        
    if(first=='7' && second=='O' && third=='O'){
      Serial.println("MK_7-NO_1 Opened");
     myBot.sendTo(userid, "MK_7-NO_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK7O="MK_7-NO_1 Opened";
    }

      if(first=='7' && second=='C' && third=='C'){
      Serial.println("MK_7-NC_1 Closed");
     myBot.sendTo(userid, "MK_7-NC_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK7C="MK_7-NC_1 Closed";
    }
        
    if(first=='7' && second=='C' && third=='O'){
      Serial.println("MK_7-NC_1 Opened");
     myBot.sendTo(userid, "MK_7-NC_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK7C="MK_7-NC_1 Opened";
    }  
//---

//-----------------MK 8------------
if(first=='8' && second=='O' && third=='C'){
      Serial.println("MK_8-NO_1 Closed");
     myBot.sendTo(userid, "MK_8-NO_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK8O="MK_8-NO_1 Closed";
    }
        
    if(first=='8' && second=='O' && third=='O'){
      Serial.println("MK_8-NO_1 Opened");
     myBot.sendTo(userid, "MK_8-NO_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK8O="MK_8-NO_1 Opened";
    }

      if(first=='8' && second=='C' && third=='C'){
      Serial.println("MK_8-NC_1 Closed");
     myBot.sendTo(userid, "MK_8-NC_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK8C="MK_8-NC_1 Closed";
    }
        
    if(first=='8' && second=='C' && third=='O'){
      Serial.println("MK_8-NC_1 Opened");
     myBot.sendTo(userid, "MK_8-NC_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK8C="MK_8-NC_1 Opened";
    }  
//---

//-----------------MK 9------------
if(first=='9' && second=='O' && third=='C'){
      Serial.println("MK_9-NO_1 Closed");
     myBot.sendTo(userid, "MK_9-NO_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK9O="MK_9-NO_1 Closed";
    }
        
    if(first=='9' && second=='O' && third=='O'){
      Serial.println("MK_9-NO_1 Opened");
     myBot.sendTo(userid, "MK_9-NO_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK9O="MK_9-NO_1 Opened";
    }

      if(first=='9' && second=='C' && third=='C'){
      Serial.println("MK_9-NC_1 Closed");
     myBot.sendTo(userid, "MK_9-NC_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK9C="MK_9-NC_1 Closed";
    }
        
    if(first=='9' && second=='C' && third=='O'){
      Serial.println("MK_9-NC_1 Opened");
     myBot.sendTo(userid, "MK_9-NC_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK9C="MK_9-NC_1 Opened";
    }  
//---

//-----------------MK 10------------
if(first=='A' && second=='O' && third=='C'){
      Serial.println("MK_10-NO_1 Closed");
     myBot.sendTo(userid, "MK_10-NO_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK10O="MK_10-NO_1 Closed";
    }
        
    if(first=='A' && second=='O' && third=='O'){
      Serial.println("MK_10-NO_1 Opened");
     myBot.sendTo(userid, "MK_10-NO_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK10O="MK_10-NO_1 Opened";
    }

      if(first=='A' && second=='C' && third=='C'){
      Serial.println("MK_10-NC_1 Closed");
     myBot.sendTo(userid, "MK_10-NC_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK10C="MK_10-NC_1 Closed";
    }
        
    if(first=='A' && second=='C' && third=='O'){
      Serial.println("MK_10-NC_1 Opened");
     myBot.sendTo(userid, "MK_10-NC_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK10C="MK_10-NC_1 Opened";
    }  
//---

//-----------------MK 11------------
if(first=='B' && second=='O' && third=='C'){
      Serial.println("MK_11-NO_1 Closed");
     myBot.sendTo(userid, "MK_11-NO_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK11O="MK_11-NO_1 Closed";
    }
        
    if(first=='B' && second=='O' && third=='O'){
      Serial.println("MK_11-NO_1 Opened");
     myBot.sendTo(userid, "MK_11-NO_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK11O="MK_11-NO_1 Opened";
    }

      if(first=='B' && second=='C' && third=='C'){
      Serial.println("MK_11-NC_1 Closed");
     myBot.sendTo(userid, "MK_11-NC_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK11C="MK_11-NC_1 Closed";
    }
        
    if(first=='B' && second=='C' && third=='O'){
      Serial.println("MK_11-NC_1 Opened");
     myBot.sendTo(userid, "MK_11-NC_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK11C="MK_11-NC_1 Opened";
    }  
//---



//-----------------MK 12------------
if(first=='C' && second=='O' && third=='C'){
      Serial.println("MK_12-NO_1 Closed");
     myBot.sendTo(userid, "MK_12-NO_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK12O="MK_12-NO_1 Closed";
    }
        
    if(first=='C' && second=='O' && third=='O'){
      Serial.println("MK_12-NO_1 Opened");
     myBot.sendTo(userid, "MK_12-NO_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK12O="MK_12-NO_1 Opened";
    }

      if(first=='C' && second=='C' && third=='C'){
      Serial.println("MK_12-NC_1 Closed");
     myBot.sendTo(userid, "MK_12-NC_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK12C="MK_12-NC_1 Closed";
    }
        
    if(first=='C' && second=='C' && third=='O'){
      Serial.println("MK_12-NC_1 Opened");
     myBot.sendTo(userid, "MK_12-NC_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK12C="MK_12-NC_1 Opened";
    }  
//---


//-----------------MK 13------------
if(first=='D' && second=='O' && third=='C'){
      Serial.println("MK_13-NO_1 Closed");
     myBot.sendTo(userid, "MK_13-NO_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK13O="MK_13-NO_1 Closed";
    }
        
    if(first=='D' && second=='O' && third=='O'){
      Serial.println("MK_13-NO_1 Opened");
     myBot.sendTo(userid, "MK_13-NO_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK13O="MK_13-NO_1 Opened";
    }

      if(first=='D' && second=='C' && third=='C'){
      Serial.println("MK_13-NC_1 Closed");
     myBot.sendTo(userid, "MK_13-NC_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK13C="MK_13-NC_1 Closed";
    }
        
    if(first=='D' && second=='C' && third=='O'){
      Serial.println("MK_13-NC_1 Opened");
     myBot.sendTo(userid, "MK_13-NC_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK13C="MK_13-NC_1 Opened";
    }  
//---


//-----------------MK 14------------
if(first=='E' && second=='O' && third=='C'){
      Serial.println("MK_14-NO_1 Closed");
     myBot.sendTo(userid, "MK_14-NO_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK14O="MK_14-NO_1 Closed";
    }
        
    if(first=='E' && second=='O' && third=='O'){
      Serial.println("MK_14-NO_1 Opened");
     myBot.sendTo(userid, "MK_14-NO_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK14O="MK_14-NO_1 Opened";
    }

      if(first=='E' && second=='C' && third=='C'){
      Serial.println("MK_14-NC_1 Closed");
     myBot.sendTo(userid, "MK_14-NC_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK14C="MK_14-NC_1 Closed";
    }
        
    if(first=='E' && second=='C' && third=='O'){
      Serial.println("MK_14-NC_1 Opened");
     myBot.sendTo(userid, "MK_14-NC_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK14C="MK_14-NC_1 Opened";
    }  
//---

//-----------------MK 15------------
if(first=='F' && second=='O' && third=='C'){
      Serial.println("MK_15-NO_1 Closed");
     myBot.sendTo(userid, "MK_15-NO_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK15O="MK_15-NO_1 Closed";
    }
        
    if(first=='F' && second=='O' && third=='O'){
      Serial.println("MK_15-NO_1 Opened");
     myBot.sendTo(userid, "MK_15-NO_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK15O="MK_15-NO_1 Opened";
    }

      if(first=='F' && second=='C' && third=='C'){
      Serial.println("MK_15-NC_1 Closed");
     myBot.sendTo(userid, "MK_15-NC_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK15C="MK_15-NC_1 Closed";
    }
        
    if(first=='F' && second=='C' && third=='O'){
      Serial.println("MK_15-NC_1 Opened");
     myBot.sendTo(userid, "MK_15-NC_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK15C="MK_15-NC_1 Opened";
    }  
//---



//-----------------MK 16------------
if(first=='G' && second=='O' && third=='C'){
      Serial.println("MK_16-NO_1 Closed");
     myBot.sendTo(userid, "MK_16-NO_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK16O="MK_16-NO_1 Closed";
    }
        
    if(first=='G' && second=='O' && third=='O'){
      Serial.println("MK_16-NO_1 Opened");
     myBot.sendTo(userid, "MK_16-NO_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK16O="MK_16-NO_1 Opened";
    }

      if(first=='G' && second=='C' && third=='C'){
      Serial.println("MK_16-NC_1 Closed");
     myBot.sendTo(userid, "MK_16-NC_1 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK16C="MK_16-NC_1 Closed";
    }
        
    if(first=='G' && second=='C' && third=='O'){
      Serial.println("MK_16-NC_1 Opened");
     myBot.sendTo(userid, "MK_16-NC_1 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK16C="MK_16-NC_1 Opened";
    }  
//---



    if (data.length()>0) {
    //myBot.sendMessage(msg, " tamat");
    delay(10);
    //data = "";
  }

  
}
