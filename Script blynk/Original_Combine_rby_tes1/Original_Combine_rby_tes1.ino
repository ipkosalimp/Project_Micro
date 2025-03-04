#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define pinpompa 5
#define pinlampu 4
#define pindatacahaya 0
#define pindatatanah 2
#define pinsensorcahaya 10
#define pinsensortanah A0  
#define batastanah 500


#define BLYNK_TEMPLATE_ID           "TMPL6k4FNckSO"
#define BLYNK_TEMPLATE_NAME         "SmarthomeBandung"
#define BLYNK_AUTH_TOKEN            "D_G8uI8kEiExjVehj2IZiMnNWe-FKPEA"

int sensorcahaya;
int sensortanah;

char ssid[] = "elfmiracle";
char pass[] = "everlastingfriend";

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(pinpompa,pinValue);
  Serial.print("V1 ");
  
}
BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(pinlampu,pinValue);
Serial.print("V2 ");
}


void setup()
{
  Serial.begin(9600);
  pinMode(pinpompa,OUTPUT);
  pinMode(pinlampu,OUTPUT);
  pinMode(pindatacahaya,OUTPUT);
  pinMode(pindatatanah,OUTPUT);
  pinMode(pinsensorcahaya,INPUT);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass,"blynk.cloud", 8080);
}

void loop()
{
  sensorcahaya=digitalRead(pinsensorcahaya);
  Blynk.run();
  sensortanah=analogRead(pinsensortanah);
  Blynk.virtualWrite(V3, sensortanah);
  Blynk.virtualWrite(V4, sensorcahaya);
  
  if(sensorcahaya==0) digitalWrite(pindatacahaya,LOW);
  if(sensorcahaya==1) digitalWrite(pindatacahaya,HIGH);
  if(sensortanah>batastanah) digitalWrite(pindatatanah,HIGH);
  if(sensortanah<batastanah) digitalWrite(pindatatanah,LOW);
  delay(100);
  
  Serial.print(sensorcahaya);
  Serial.print("  ");
  Serial.println(sensortanah);
  
}
