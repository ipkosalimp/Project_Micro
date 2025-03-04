#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID           "TMPL6k4FNckSO"
#define BLYNK_TEMPLATE_NAME         "SmarthomeBandung"
#define BLYNK_AUTH_TOKEN            "D_G8uI8kEiExjVehj2IZiMnNWe-FKPEA"

char ssid[] = "XiaomiPad6";
char pass[] = "ipkosalimp";

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(2,pinValue);
  
}
BLYNK_WRITE(V3)
{
  int slider = param.asInt(); // assigning incoming value from pin V1 to a variable
  analogWrite(4,slider);
  // process received value
}

void setup()
{
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass,"blynk.cloud", 8080);
}

void loop()
{
  Blynk.run();
  int pot=analogRead(A0);
  Blynk.virtualWrite(V2, pot);
}
