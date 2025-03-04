/*
  Name        : echoBot.ino
  Created     : 26/03/2021
  Author      : Tolentino Cotesta <cotestatnt@yahoo.com>
  Description : a simple example that check for incoming messages
                and reply the sender with the received message.
                The message will be forwarded also in a public channel
                anad to a specific userid.
*/

/*
  Set true if you want use external library for SSL connection instead ESP32@WiFiClientSecure
  For example https://github.com/OPEnSLab-OSU/SSLClient/ is very efficient BearSSL library.
  You can use AsyncTelegram2 even with other MCUs or transport layer (ex. Ethernet)
  With SSLClient, be sure "certificates.h" file is present in sketch folder
*/

/*
                              _             _____   _____   _____   _____
                             | |           |_   _| / ____| |_   _| |  __ \
                        _   _| | ___   __ _  | |  | |        | |   | |  | |
                       | | | | |/ _ \ / _` | | |  | |        | |   | |  | |
                       | |_| | | (_) | (_| |_| |_ | |____ _ _| |_  | |__| |
                       | ._,_|_|\___/ \__, |_____| \_____(_)_____| |_____/
                       | |             __/ |       ulogic.id@gmail.com
                       |_|            |___/


   21/02/2021 - μlogIC.ID
   ulogic.id@gmail.com
   MicroLogic Indonesia
   Penggunaan library Telegram BOT - CTBot untuk mengirimkan kembali pesan ang diterima BOT
   Board    : ESP32 DEVKITV1 (ESP32) kompatibel dengan ESP8266
   IDE      : Arduino IDE 1.8.16
   Core     : esp32 1.0.6
   Library  : 1. AsyncTelegram2 (2.0.8)   Tolentino Cotesta (https://github.com/cotestatnt/asynctelegram2)
              2. SSLClient (1.6.11)       OPEnS Lab (https://github.com/OPEnSLab-OSU/SSLClient)
              3. ArduinoJson (6.19.2)     Benoit Blanchon (https://arduinojson.org/)

   Flow     : 1. Built-in LED akan berkedip terus menerus dengan interval 150 ms
              2. Bersamaan dengan itu, cek apakah ada pesan yang diterima. Kirim
                 kembali pesan yang sama ketika ada pesan yang diterima.
*/

#define USE_CLIENTSSL true

#include <AsyncTelegram2.h>

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

// SSID dan Password WIFI
const char* ssid  =  "elfmiracle";     // SSID WiFi network
const char* pass  =  "everlastingfriend";     // Password  WiFi network

// Token Telegram yang diperoleh ketika membuat BOT lewat BotFather
const char* token =  "7190192639:AAGOV0xjya-a2pnsCKCcpQxgYr2VRnQ0vlg";  // Telegram token

void setup() {
  // Set LED_BUILTIN sebagai output
  pinMode(LED_BUILTIN, OUTPUT);
  // inisialisasi serial
  Serial.begin(115200);
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
  int64_t userid = 772223457;
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

  // Ketika ada pesan masuk, tulis di serial monitor dan
  // balas pesan yang sama ke pengirim pesan
  if (myBot.getNewMessage(msg)) {
    // Send a message to your public channel
    String message ;
    message += "Message from @";
    message += myBot.getBotName();
    message += ":\n";
    message += msg.text;
    Serial.println(message);
    myBot.sendMessage(msg, msg.text);
    if (msg.text.equalsIgnoreCase("TEST")) {              
      myBot.sendMessage(msg,"IPKO GANTENG COY");  //kirim pesan ke bot telegram
    }
  }
}
