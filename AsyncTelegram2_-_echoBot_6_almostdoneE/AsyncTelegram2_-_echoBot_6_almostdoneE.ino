
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
#include<EEPROM.h>
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
const char* ssid  =  "elfmiracle";     // SSID WiFi network
const char* pass  =  "everlastingfriend";     // Password  WiFi network

// Token Telegram yang diperoleh ketika membuat BOT lewat BotFather
const char* token =  "7190192639:AAGOV0xjya-a2pnsCKCcpQxgYr2VRnQ0vlg";  // Telegram token
//int64_t userid = -4175257531; //id grup

String data;
char c;

// STATUS-> 1 closed, 0 open
byte opened=0;    //--> logic bisa diganti
byte closed=1;
byte MK1=0;
byte MK2=0;
byte MK3=0;
byte MK4=0;
byte MK5=0;
byte MK6=0;
byte MK7=0;
byte MK8=0;
byte MK9=0;
byte MK10=0;
byte MK11=0;
byte MK12=0;
byte MK13=0;
byte MK14=0;
byte MK15=0;
byte MK16=0;
byte MK17=0;
byte MK18=0;
byte MK19=0;
byte MK20=0;
byte MK21=0;
byte MK22=0;
byte MK23=0;
byte MK24=0;
byte MK25=0;
byte MK26=0;
byte MK27=0;
byte MK28=0;
byte MK29=0;
byte MK30=0;
byte MK31=0;
byte MK32=0;
byte MK1_F=0;
byte MK2_F=0;
byte MK3_F=0;
byte MK4_F=0;
byte MK5_F=0;
byte MK6_F=0;
byte MK7_F=0;
byte MK8_F=0;
byte MK9_F=0;
byte MK10_F=0;
byte MK11_F=0;
byte MK12_F=0;
byte MK13_F=0;
byte MK14_F=0;
byte MK15_F=0;
byte MK16_F=0;
byte MK17_F=0;
byte MK18_F=0;
byte MK19_F=0;
byte MK20_F=0;
byte MK21_F=0;
byte MK22_F=0;
byte MK23_F=0;
byte MK24_F=0;
byte MK25_F=0;
byte MK26_F=0;
byte MK27_F=0;
byte MK28_F=0;
byte MK29_F=0;
byte MK30_F=0;
byte MK31_F=0;
byte MK32_F=0;
String message ;
int64_t userid = -4128298459; //id grup

#define MK1_EE 1
#define MK2_EE 2
#define MK3_EE 3
#define MK4_EE 4
#define MK5_EE 5
#define MK6_EE 6
#define MK7_EE 7
#define MK8_EE 8
#define MK9_EE 9
#define MK10_EE 10
#define MK11_EE 11
#define MK12_EE 12
#define MK13_EE 13
#define MK14_EE 14
#define MK15_EE 15
#define MK16_EE 16
#define MK17_EE 17
#define MK18_EE 18
#define MK19_EE 19
#define MK20_EE 20
#define MK21_EE 21
#define MK22_EE 22
#define MK23_EE 23
#define MK24_EE 24
#define MK25_EE 25
#define MK26_EE 26
#define MK27_EE 27
#define MK28_EE 28
#define MK29_EE 29
#define MK30_EE 30
#define MK31_EE 31
#define MK32_EE 32

void setup() {
  // Set LED_BUILTIN sebagai output
  EEPROM.begin(40);
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
  //int64_t userid = 5696629558;
  //int64_t userid = -4175257531; //id grup
  //-> token -> 7190192639:AAGOV0xjya-a2pnsCKCcpQxgYr2VRnQ0vlg
  
  myBot.sendTo(userid, welcome_msg);
}



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
    else if (msg.text.equalsIgnoreCase("STATUS")) {              
      myBot.sendMessage(msg,"Cek status");  //kirim pesan ke bot telegram
    LOAD();
    }
    else if (msg.text.equalsIgnoreCase("CALL")) {              
    myBot.sendMessage(msg,"Calibration");  //kirim pesan ke bot telegram
    sserial.print("CL");
     sserial.print("#");
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

    char first=data.charAt(0);
    char second=data.charAt(1);
    char third=data.charAt(2);
    char forth=data.charAt(3);
//    Serial.print("GABUNG= ");
//    Serial.print(data);
//    Serial.print("----- By Slot= ");
//    
//    Serial.print(first);
//    Serial.print(" ");
//    Serial.print(second);
//    Serial.print(" ");
//    Serial.print(third);
//    Serial.print(" ");
//    Serial.print(forth);
//    Serial.println(" ");


    if (data.length()>0) {
    //myBot.sendMessage(msg, " tamat");
    delay(10);
    data = "";
  }

//-----------------MK 1------------
    if(first=='1' && second=='O' && third=='C'){
      Serial.println("CB CLOSED KRAKSAAN 1");    
      myBot.sendTo(userid, "CB CLOSED KRAKSAAN 1");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK1=closed;
      EEPROM.write(MK1_EE,MK1);
    }
        
    if(first=='1' && second=='O' && third=='O'){
      Serial.println("CB OPEN KRAKSAAN 1");
      myBot.sendTo(userid,"CB OPEN KRAKSAAN 1");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK1=opened;
      EEPROM.write(MK1_EE,MK1);
    }

    
//-----------------MK 2------------
      if(first=='1' && second=='C' && third=='C'){
      Serial.println("CB CLOSED KRAKSAAN 2");
      myBot.sendTo(userid,"CB CLOSED KRAKSAAN 2");
      //delay(500);
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK2=closed;
      EEPROM.write(MK2_EE,MK2);
    }
        
    if(first=='1' && second=='C' && third=='O'){
      Serial.println("CB OPEN KRAKSAAN 2");
      myBot.sendTo(userid,"CB OPEN KRAKSAAN 2");
      //delay(500);
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK2=opened;
      EEPROM.write(MK2_EE,MK2);
    }
//------



//-----------------MK 3------------
if(first=='2' && second=='O' && third=='C'){
      Serial.println("CB CLOSED GONDANG 1");
     myBot.sendTo(userid, "CB CLOSED GONDANG 1");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK3=closed;
      EEPROM.write(MK3_EE,MK3);
    }
        
    if(first=='2' && second=='O' && third=='O'){
      Serial.println("CB OPEN GONDANG 1");
      myBot.sendTo(userid, "CB OPEN GONDANG 1");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK3=opened;
      EEPROM.write(MK3_EE,MK3);
    }



//-----------------MK 4------------
      if(first=='2' && second=='C' && third=='C'){
      Serial.println("CB CLOSED GONDANG 2");
      myBot.sendTo(userid, "CB CLOSED GONDANG 2");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK4=closed;
      EEPROM.write(MK4_EE,MK4);
    }
        
    if(first=='2' && second=='C' && third=='O'){
      Serial.println("CB OPEN GONDANG 2");
      myBot.sendTo(userid, "CB OPEN GONDANG 2");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK4=opened;
      EEPROM.write(MK4_EE,MK4);
    }  
//---

//-----------------MK 5------------
if(first=='3' && second=='O' && third=='C'){
      Serial.println("CB CLOSE LUMAJANG 1");
     myBot.sendTo(userid, "CB CLOSE LUMAJANG 1");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK5=closed;
      EEPROM.write(MK5_EE,MK5);
    }
        
    if(first=='3' && second=='O' && third=='O'){
      Serial.println("CB OPEN LUMAJANG 1");
     myBot.sendTo(userid, "CB OPEN LUMAJANG 1");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      MK5=opened;
      EEPROM.write(MK5_EE,MK5);
    }

//-----------------MK 6------------
      if(first=='3' && second=='C' && third=='C'){
      Serial.println("CB CLOSE LUMAJANG 2");
      myBot.sendTo(userid, "CB CLOSE LUMAJANG 2");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }
        
    if(first=='3' && second=='C' && third=='O'){
      Serial.println("CB OPEN LUMAJANG 2");
      myBot.sendTo(userid, "CB OPEN LUMAJANG 2");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }  
//---

//-----------------MK 7------------
if(first=='4' && second=='O' && third=='C'){
      Serial.println("CB CLOSE TRAFO 1");
      myBot.sendTo(userid, "CB CLOSE TRAFO 1");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }
        
    if(first=='4' && second=='O' && third=='O'){
      Serial.println("CB OPEN TRAFO 1");
      myBot.sendTo(userid, "CB OPEN TRAFO 1");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }

//-----------------MK 8------------
      if(first=='4' && second=='C' && third=='C'){
      Serial.println("CB CLOSE TRAFO 2");
      myBot.sendTo(userid, "CB CLOSE TRAFO 2");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }
        
    if(first=='4' && second=='C' && third=='O'){
      Serial.println("CB OPEN TRAFO 2");
     myBot.sendTo(userid, "CB OPEN TRAFO 2");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }  
//---

//-----------------MK 9------------
if(first=='5' && second=='O' && third=='C'){
      Serial.println("CB CLOSE TRAFO 3");
     myBot.sendTo(userid, "CB CLOSE TRAFO 3");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }
        
    if(first=='5' && second=='O' && third=='O'){
      Serial.println("CB OPEN TRAFO 3");
     myBot.sendTo(userid, "CB OPEN TRAFO 3");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }

//-----------------MK 10------------
      if(first=='5' && second=='C' && third=='C'){
      Serial.println("CB CLOSE KOPEL");
     myBot.sendTo(userid, "CB CLOSE KOPEL");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }
        
    if(first=='5' && second=='C' && third=='O'){
      Serial.println("CB OPEN KOPEL");
     myBot.sendTo(userid, "CB OPEN KOPEL");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
    
    }  
//---


//-----------------MK 11------------
if(first=='6' && second=='O' && third=='C'){
      Serial.println("MK_11 Closed");
     myBot.sendTo(userid, "MK_11 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }
        
    if(first=='6' && second=='O' && third=='O'){
      Serial.println("MK_11 Opened");
     myBot.sendTo(userid, "MK_11 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }

//-----------------MK 12------------
      if(first=='6' && second=='C' && third=='C'){
      Serial.println("MK_12 Closed");
     myBot.sendTo(userid, "MK_12 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }
        
    if(first=='6' && second=='C' && third=='O'){
      Serial.println("MK_12 Opened");
     myBot.sendTo(userid, "MK_12 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }  
//---

//-----------------MK 13------------
if(first=='7' && second=='O' && third=='C'){
      Serial.println("MK_13 Closed");
     myBot.sendTo(userid, "MK_13 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }
        
    if(first=='7' && second=='O' && third=='O'){
      Serial.println("MK_13 Opened");
     myBot.sendTo(userid, "MK_13 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }

//-----------------MK 14------------
      if(first=='7' && second=='C' && third=='C'){
      Serial.println("MK_14 Closed");
     myBot.sendTo(userid, "MK_14 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }
        
    if(first=='7' && second=='C' && third=='O'){
      Serial.println("MK_14 Opened");
     myBot.sendTo(userid, "MK_14 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }  
//---

//-----------------MK 15------------
if(first=='8' && second=='O' && third=='C'){
      Serial.println("MK_15 Closed");
     myBot.sendTo(userid, "MK_15 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }
        
    if(first=='8' && second=='O' && third=='O'){
      Serial.println("MK_15 Opened");
     myBot.sendTo(userid, "MK_15 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }

//-----------------MK 16------------
      if(first=='8' && second=='C' && third=='C'){
      Serial.println("MK_16 Closed");
     myBot.sendTo(userid, "MK_16 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }
        
    if(first=='8' && second=='C' && third=='O'){
      Serial.println("MK_16 Opened");
     myBot.sendTo(userid, "MK_16 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }  
//---



//----Kebawah diasumsikan kontak normaly close (NC)-----//
//-----------------MK 17------------
if(first=='9' && second=='O' && third=='C'){
      Serial.println("MK_17 Closed");
     myBot.sendTo(userid, "MK_17 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }
        
    if(first=='9' && second=='O' && third=='O'){
      Serial.println("MK_17 Opened");
     myBot.sendTo(userid, "MK_17 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }



//-----------------MK 18------------
      if(first=='9' && second=='C' && third=='C'){
      Serial.println("MK_18 Closed");
     myBot.sendTo(userid, "MK_18 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }
        
    if(first=='9' && second=='C' && third=='O'){
      Serial.println("MK_18 Opened");
     myBot.sendTo(userid, "MK_18 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }  
//---

//-----------------MK 19------------
if(first=='A' && second=='O' && third=='C'){
      Serial.println("MK_19 Closed");
     myBot.sendTo(userid, "MK_19 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }
        
    if(first=='A' && second=='O' && third=='O'){
      Serial.println("MK_19 Opened");
     myBot.sendTo(userid, "MK_19 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }


//-----------------MK 20------------
      if(first=='A' && second=='C' && third=='C'){
      Serial.println("MK_20 Closed");
     myBot.sendTo(userid, "MK_20 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }
        
    if(first=='A' && second=='C' && third=='O'){
      Serial.println("MK_20 Opened");
     myBot.sendTo(userid, "MK_20 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }  


//-----------------MK 21------------
if(first=='B' && second=='O' && third=='C'){
      Serial.println("MK_21 Closed");
     myBot.sendTo(userid, "MK_21 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }
        
    if(first=='B' && second=='O' && third=='O'){
      Serial.println("MK_21 Opened");
     myBot.sendTo(userid, "MK_21 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }


//-----------------MK 22------------
      if(first=='B' && second=='C' && third=='C'){
      Serial.println("MK_22 Closed");
     myBot.sendTo(userid, "MK_22 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }
        
    if(first=='B' && second=='C' && third=='O'){
      Serial.println("MK_22 Opened");
     myBot.sendTo(userid, "MK_22 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }  
//---



//-----------------MK 23------------
if(first=='C' && second=='O' && third=='C'){
      Serial.println("MK_23 Closed");
     myBot.sendTo(userid, "MK_23 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }
        
    if(first=='C' && second=='O' && third=='O'){
      Serial.println("MK_23 Opened");
     myBot.sendTo(userid, "MK_23 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }

//-----------------MK 24------------
      if(first=='C' && second=='C' && third=='C'){
      Serial.println("MK_24 Closed");
     myBot.sendTo(userid, "MK_24 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }
        
    if(first=='C' && second=='C' && third=='O'){
      Serial.println("MK_24 Opened");
     myBot.sendTo(userid, "MK_24 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
    
    }  



//-----------------MK 25------------
if(first=='D' && second=='O' && third=='C'){
      Serial.println("MK_25 Closed");
     myBot.sendTo(userid, "MK_25 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }
        
    if(first=='D' && second=='O' && third=='O'){
      Serial.println("MK_25 Opened");
     myBot.sendTo(userid, "MK_25 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }


//-----------------MK 26------------
      if(first=='D' && second=='C' && third=='C'){
      Serial.println("MK_26 Closed");
     myBot.sendTo(userid, "MK_26 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }
        
    if(first=='D' && second=='C' && third=='O'){
      Serial.println("MK_26 Opened");
     myBot.sendTo(userid, "MK_26 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }  



//-----------------MK 27------------
if(first=='E' && second=='O' && third=='C'){
      Serial.println("MK_27 Closed");
     myBot.sendTo(userid, "MK_27 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }
        
    if(first=='E' && second=='O' && third=='O'){
      Serial.println("MK_27 Opened");
     myBot.sendTo(userid, "MK_27 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }



//-----------------MK 28------------
      if(first=='E' && second=='C' && third=='C'){
      Serial.println("MK_28 Closed");
     myBot.sendTo(userid, "MK_28 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }
        
    if(first=='E' && second=='C' && third=='O'){
      Serial.println("MK_28 Opened");
     myBot.sendTo(userid, "MK_28 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }  


//-----------------MK 29------------
if(first=='F' && second=='O' && third=='C'){
      Serial.println("MK_29 Closed");
     myBot.sendTo(userid, "MK_29 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }
        
    if(first=='F' && second=='O' && third=='O'){
      Serial.println("MK_29 Opened");
     myBot.sendTo(userid, "MK_29 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }


//-----------------MK 30------------
      if(first=='F' && second=='C' && third=='C'){
      Serial.println("MK_30 Closed");
     myBot.sendTo(userid, "MK_30 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }
        
    if(first=='F' && second=='C' && third=='O'){
      Serial.println("MK_30 Opened");
     myBot.sendTo(userid, "MK_30 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }  



//-----------------MK 31------------
if(first=='G' && second=='O' && third=='C'){
      Serial.println("MK_31 Closed");
     myBot.sendTo(userid, "MK_31 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
      
    }
        
    if(first=='G' && second=='O' && third=='O'){
      Serial.println("MK_31 Opened");
     myBot.sendTo(userid, "MK_31 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }


//-----------------MK 32------------
      if(first=='G' && second=='C' && third=='C'){
      Serial.println("MK_32 Closed");
     myBot.sendTo(userid, "MK_32 Closed");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
    
    }
        
    if(first=='G' && second=='C' && third=='O'){
      Serial.println("MK_32 Opened");
     myBot.sendTo(userid, "MK_32 Opened");
      first=' ';
      second=' ';
      if(forth=='#') data = "";
     
    }  
//---



    if (data.length()>0) {
    //myBot.sendMessage(msg, " tamat");
    delay(10);
    //data = "";
  }

  
}
void LOAD(){
MK1_F=EEPROM.read(MK1_EE);
MK2_F=EEPROM.read(MK2_EE);
MK3_F=EEPROM.read(MK3_EE);
MK4_F=EEPROM.read(MK4_EE);
MK5_F=EEPROM.read(MK5_EE);
MK6_F=EEPROM.read(MK6_EE);
MK7_F=EEPROM.read(MK7_EE);
MK8_F=EEPROM.read(MK8_EE);
MK9_F=EEPROM.read(MK9_EE);
MK10_F=EEPROM.read(MK10_EE);
MK11_F=EEPROM.read(MK11_EE);
MK12_F=EEPROM.read(MK12_EE);
MK13_F=EEPROM.read(MK13_EE);
MK14_F=EEPROM.read(MK14_EE);
MK15_F=EEPROM.read(MK15_EE);
MK16_F=EEPROM.read(MK16_EE);
MK17_F=EEPROM.read(MK17_EE);
MK18_F=EEPROM.read(MK18_EE);
MK19_F=EEPROM.read(MK19_EE);
MK20_F=EEPROM.read(MK20_EE);
MK21_F=EEPROM.read(MK21_EE);
MK22_F=EEPROM.read(MK22_EE);
MK23_F=EEPROM.read(MK23_EE);
MK24_F=EEPROM.read(MK24_EE);
MK25_F=EEPROM.read(MK25_EE);
MK26_F=EEPROM.read(MK26_EE);
MK27_F=EEPROM.read(MK27_EE);
MK28_F=EEPROM.read(MK28_EE);
MK29_F=EEPROM.read(MK29_EE);
MK30_F=EEPROM.read(MK30_EE);
MK31_F=EEPROM.read(MK31_EE);
MK32_F=EEPROM.read(MK32_EE);

Serial.print("  MK1_E:");
Serial.print(MK1_F);
Serial.print("  MK2_E:");
Serial.print(MK2_F);
Serial.print("  MK3_E:");
Serial.print(MK3_F);
Serial.print("  MK4_E:");
Serial.print(MK4_F);
Serial.print("  MK5_E:");
Serial.print(MK5_F);
Serial.print("  MK6_E:");
Serial.print(MK6_F);
Serial.print("  MK7_E:");
Serial.print(MK7_F);
Serial.print("  MK8_E:");
Serial.print(MK8_F);
Serial.print("  MK9_E:");
Serial.print(MK9_F);
Serial.print("  MK10_E:");
Serial.print(MK10_F);
Serial.print("  MK11_E:");
Serial.print(MK11_F);
Serial.print("  MK12_E:");
Serial.print(MK12_F);
Serial.print("  MK13_E:");
Serial.print(MK13_F);
Serial.print("  MK14_E:");
Serial.print(MK14_F);
Serial.print("  MK15_E:");
Serial.print(MK15_F);
Serial.print("  MK16_E:");
Serial.print(MK16_F);
Serial.print("  MK17_E:");
Serial.print(MK17_F);
Serial.print("  MK18_E:");
Serial.print(MK18_F);
Serial.print("  MK19_E:");
Serial.print(MK19_F);
Serial.print("  MK20_E:");
Serial.print(MK20_F);
Serial.print("  MK21_E:");
Serial.print(MK21_F);
Serial.print("  MK22_E:");
Serial.print(MK22_F);
Serial.print("  MK23_E:");
Serial.print(MK23_F);
Serial.print("  MK24_E:");
Serial.print(MK24_F);
Serial.print("  MK25_E:");
Serial.print(MK25_F);
Serial.print("  MK26_E:");
Serial.print(MK26_F);
Serial.print("  MK27_E:");
Serial.print(MK27_F);
Serial.print("  MK28_E:");
Serial.print(MK28_F);
Serial.print("  MK29_E:");
Serial.print(MK29_F);
Serial.print("  MK30_E:");
Serial.print(MK30_F);
Serial.print("  MK31_E:");
Serial.print(MK31_F);
Serial.print("  MK32_E:");
Serial.println(MK32_F);
delay(1000);


}
