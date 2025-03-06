/*
   Project Name : Monitoring AC Kolator
   Instansi     : PT.Sarana Makin Mulia
   Departemen   : Engineering
   Last Update  : Kamis,22 Agustus 2024

   Arduino Version    : 1.8.16
   Hardware           : - Node MCU ESP32
                        - TSOP 1738
                        - Infrared Transmitter
                        x Current meter PZEM 004
                        x Ethernet ENC28J60
                        - DHT22 
                        - OLED 1306
   
   Update :
            - Send Data remote ON/OFF to Air Conditioner
            - 
    
    Library:
    - Adafruit_SSD1306.h  V 2.4.0 (Libraries Manager)
    - IR Remote by danny source (https://github.com/danny-source/Arduino_DY_IRDaikin)
    - Current meter PZEM 004 (https://github.com/mandulaj/PZEM-004T-v30
    - [optional] Ethernet ENC28J60 (https://www.instructables.com/Arduino-Webserver-Controller-Using-Ethernet-ENC28J/)
    - DHT 11 by Jofel Batutay V 1.0.1(Libraries Manager)
    - UTF8 Print AdaGfx library V 1.0.2

   
*/

//--- Init IR
#include <DYIRDaikin.h>

//#define DYIRDAIKIN_SOFT_IR

DYIRDaikin irdaikin;
int isOn;


//---Init OLED
#include <SPI.h>
#include <Wire.h>
//#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16


void setup()
{
	Serial.begin(115200);
////
  display.setTextSize(1); // Draw 2X-scale text(1=7px, 2=14px it means 2 times from the pixel)
  display.setTextColor(WHITE);
  display.cp437(true);     
//  display.clearDisplay();
  
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.setCursor(0, 0);
  display.print("PT.SMM");
  display.setCursor(0, 10);
  display.print("Monitoring");
  display.display();
  delay(2000); // Pause for 2 seconds
  // Clear the buffer
  display.clearDisplay();
  //


 
 while(!Serial.available());
 Serial.println("Begin");
	#ifdef DYIRDAIKIN_SOFT_IR
	irdaikin.begin(5);
	#else
	irdaikin.begin(5);
	#endif
	irdaikin.on();
	irdaikin.setSwing_off();
	irdaikin.setMode(1);
	irdaikin.setFan(4);//FAN speed to MAX
	irdaikin.setTemp(25);
	//----everything is ok and to execute send command-----
	irdaikin.sendCommand();
	isOn = 0;
 Serial.println("END");
  
}

void loop() {
 //if (Serial.available()) {
  String income=Serial.readStringUntil('\n');
  Serial.print("Before=");
  Serial.println(income);
		if (income == "t") {
			if (isOn == 0){
				isOn = 1;
				irdaikin.off();
				Serial.println("Turn Off");
        display.setCursor(0, 36);
      display.print("AC OFF");
			}else{
				isOn = 0;
				irdaikin.on();
				Serial.println("Turn On");
        display.setCursor(0, 36);
        display.print("AC ON");
			}
			irdaikin.sendCommand();
			Serial.println("Execute Command!");
		}

   else if(income == "1"){
    irdaikin.setTemp(18);
    irdaikin.sendCommand();
    delay(100);
      Serial.println("Temp 18,Execute Command!");
      display.setCursor(0, 36);
      display.print("Set=COOL");
   }
    else  if(income == "2"){
    irdaikin.setTemp(21);
    irdaikin.sendCommand();
    delay(100);
      display.setCursor(0, 36);
      display.print("Set=21 C");
      Serial.println("Temp 21,Execute Command!");
   }

    else  if(income == "3"){
    irdaikin.setTemp(24);
    irdaikin.sendCommand();
    delay(100);
          display.setCursor(0, 36);
      display.print("Set=24 C");
      Serial.println("Temp 24,Execute Command!");
   }
   
    else if(income == "z"){
      Serial.println("TEST");
            display.setCursor(0, 36);
      display.print("-TEST-");
    }

  Serial.print("After=");
  Serial.println(income);
  Serial.print("After Clearing=");
  income=" ";
  display.display();
  Serial.println(income);
  delay(500);
  display.clearDisplay();
	//}
 Serial.println("NOT AVAILABLE");
}
