#include <SPI.h>
#include <MFRC522.h>

#include <WiFi.h>
const char AP_NameChar[] = "Autobot" ;    //SET AKSES POINT
const char WiFiPassword[] = "kaipkoganteng";    //SET PASSWORD


 
WiFiServer server(80);



#define SS_PIN 13   //D7
#define RST_PIN 15  //D8
#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
  
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_1 = "<!DOCTYPE html><html><head><title>LED Control</title></head><body><div id='main'><h2>LED Control</h2>";
String html_2 = "<form id='F1' action='LEDON'><input class='button' type='submit' value='LED ON' ></form><br>";
String html_3 = "<form id='F2' action='LEDOFF'><input class='button' type='submit' value='LED OFF' ></form><br>";
String html_4 = "</div></body></html>";
int kunci=0;
String request = "";
//int A1 = 5;  //D1
//int A2 = 0;  //D3
//int B1 = 4;  //D2
//int B2 = 2;  //D4

#define A1 13  //PWM A D1
#define A2 27  //DIR A D2
#define B1 26  //PWM B D3
#define B2 25  //DIR B D4
#define EN1 16  //PWM A D5
#define EN2 17  //PWM B D6

int motorspeed=1023;
void setup() 
{
    pinMode(A1, OUTPUT); 
    pinMode(A2, OUTPUT); 
    pinMode(B1, OUTPUT); 
    pinMode(B2, OUTPUT); 
    pinMode(EN1,OUTPUT);
    pinMode(EN2,OUTPUT);
 
    boolean conn = WiFi.softAP(AP_NameChar, WiFiPassword);
    server.begin();
    Serial.begin(115200);
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Put your card to the reader...");
  Serial.println();

} // void setup()
 
 
void loop() 
{
 
    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client)  {   return;   }
 
    // Read the first line of the request
    request = client.readStringUntil('\r');

/////////////////////////////////////

 // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "C5 94 7C 69") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(500);
  }
 
 else   {
    Serial.println(" Access denied");
  }
//////////////////////////////////////
 
    if       ( request.indexOf("FWD") > 0 )  { 
      maju();
      Serial.println("maju");  
    }
    else if  ( request.indexOf("BWD") > 0 ) { 
      mundur();
      Serial.println("mundur");  
    }
    else if  ( request.indexOf("LFT") > 0 ) { 
      kiri();
      Serial.println("kiri");  
    }
     else if  ( request.indexOf("RGT") > 0 ) { 
      kanan();
      Serial.println("kanan");  
    }
     else if  ( request.indexOf("STP") > 0 ) { 
     STOP();
      Serial.println("stop");  
    }
    else{
    
    }
 
    client.flush();
 
    client.print( header );
    client.print( html_1 );
    client.print( html_2 );
    client.print( html_3 );
    client.print( html_4);
// 
    delay(10);
    
  // The client will actually be disconnected when the function returns and 'client' object is detroyed
 
} // void loop()

void maju(){  
  analogWrite(EN1,motorspeed);
  analogWrite(EN2,motorspeed);
  digitalWrite(A1,LOW);  //low-low
  digitalWrite(A2,LOW);
  digitalWrite(B1,HIGH);  //high-high
  digitalWrite(B2,HIGH);
}

void mundur(){
  analogWrite(EN1,motorspeed);
  analogWrite(EN2,motorspeed);
  digitalWrite(A1,HIGH);  //high-high
  digitalWrite(A2,HIGH);
  digitalWrite(B1,LOW);   //low-low
  digitalWrite(B2,LOW);
}

void kiri(){
  analogWrite(EN1,motorspeed);
  analogWrite(EN2,motorspeed);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,LOW);
  digitalWrite(B1,LOW);
  digitalWrite(B2,HIGH);
}

void kanan(){
  analogWrite(EN1,motorspeed);
  analogWrite(EN2,motorspeed);
  digitalWrite(A1,LOW);
   digitalWrite(A2,HIGH);
  digitalWrite(B1,HIGH);
   digitalWrite(B2,LOW);
}

void STOP(){
  analogWrite(EN1,0);
  analogWrite(EN2,0);
  digitalWrite(A1,LOW);
  digitalWrite(B1,LOW);
  digitalWrite(A2,LOW);
  digitalWrite(B2,LOW);
}
