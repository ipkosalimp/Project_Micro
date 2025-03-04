#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
#include<EEPROM.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


int pesan[2] = {0, 1};
RF24 rf24(7, 8); //def 7,8
int16_t rssi;
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define LOGO_HEIGHT   128
#define LOGO_WIDTH    64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example




#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define pinbat A7

//byte alamat ="INO1099";
//byte ino="ino";
//int robo = 300;
//byte alamat=ino+robo;
//long int alamat=1000;
long int alamat = 140130150;

void setup() {

  display.setTextSize(1); // Draw 2X-scale text(1=7px, 2=14px it means 2 times from the pixel)
  display.setTextColor(WHITE);
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.clearDisplay();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
    display.display();
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9,OUTPUT);
  delay(100);
  rf24.begin();
  rf24.openReadingPipe(0, alamat);
  rf24.setPALevel(RF24_PA_MAX);
  rf24.startListening();
  Serial.begin(9600);
}

void loop() {
  while (rf24.available()) {
    display.clearDisplay();
    mainscreen();
    rf24.read(pesan, 2);
    if (pesan[0] == 0) {
      analogWrite(3, 0);
      analogWrite(5, 0);
      analogWrite(6, 0);
      analogWrite(9, 0);
  display.setCursor(0, 32);
  display.print("STOP");
//      Serial.println("NOL");
    } else if (pesan[0] == 1) {
      analogWrite(3, 255); //PWM
      digitalWrite(5, 1); //Logic
      digitalWrite(6, 1); //Logic
      analogWrite(9, 255); //PWM
//      Serial.println("1");
  display.setCursor(0, 32);
  display.print("1");
    }
    else if (pesan[0] == 2) {
      analogWrite(3, 255); //PWM
      digitalWrite(5, 0); //Logic
      digitalWrite(6, 0); //Logic
      analogWrite(9, 255); //PWM
//      Serial.println("2");
  display.setCursor(0, 32);
  display.print("2");
    }
    else if (pesan[0] == 3) {
      analogWrite(3, 255); //PWMA
      digitalWrite(5, 1); //LogicA
      digitalWrite(6, 0); //LogicB
      analogWrite(9, 0); //PWMB
//      Serial.println("3");
  display.setCursor(0, 32);
  display.print("3");
    }
    else if (pesan[0] == 4) {
      analogWrite(3, 0); //PWM
      digitalWrite(5, 0); //Logic
      digitalWrite(6, 1); //Logic
      analogWrite(9, 255); //PWM
//      Serial.println("4");
  display.setCursor(0, 32);
  display.print("4");
    }
    else if (pesan[0] == 5) {
//      analogWrite(3, 255);
//      analogWrite(5, 0);
//      analogWrite(6, 255);
//      Serial.println("5");
  display.setCursor(0, 32);
  display.print("5");
    }
    else if (pesan[0] == 6) {
      analogWrite(3, 255); //PWM
      digitalWrite(5, 1); //Logic
      digitalWrite(6, 1); //Logic
      analogWrite(9, 150); //PWM
//      Serial.println("6");
  display.setCursor(0, 32);
  display.print("6");
    }
    else if (pesan[0] == 7) {
      analogWrite(3, 150); //PWM
      digitalWrite(5, 1); //Logic
      digitalWrite(6, 1); //Logic
      analogWrite(9, 255); //PWM
//      Serial.println("7");
  display.setCursor(0, 32);
  display.print("7");
    }
    else if (pesan[0] == 8) {
      analogWrite(3, 150); //PWM
      digitalWrite(5, 0); //Logic
      digitalWrite(6, 0); //Logic
      analogWrite(9, 255); //PWM
//      Serial.println("8");
  display.setCursor(0, 32);
  display.print("8");
    }
    else if (pesan[0] == 9) {
      analogWrite(3, 255); //PWM
      digitalWrite(5, 0); //Logic
      digitalWrite(6, 0); //Logic
      analogWrite(9, 150); //PWM
//      Serial.println("9");
  display.setCursor(0, 32);
  display.print("9");
    }

    delay(10);
    Serial.print("Masuk RF");
    Serial.print(pesan[0]);
    Serial.print(" ");
    Serial.print(pesan[1]);
    Serial.print(" ");
    Serial.println(alamat);
  display.display();
  }
  //Serial.println("ga masuk");
}

void mainscreen(){
  display.setTextSize(2);
  display.setCursor(0, 0);      //Draw the coordinate (x,y);
  display.println("Mobile RC");
  display.setCursor(0, 16);
  display.print("LVL");
  display.setCursor(60, 16);
  rssi= rf24.getPALevel();
  
}
void splash() {
  display.setTextSize(2); // Draw 2X-scale text(1=7px, 2=14px it means 2 times from the pixel)
  display.setTextColor(WHITE);
  display.setCursor(0, 0);      //Draw the coordinate (x,y);
  display.println("Mobile RC");

  display.setTextSize(1); // Draw 2X-scale text(1=7px, 2=14px it means 2 times from the pixel)
  display.setCursor(50, 56);      //Draw the coordinate (x,y);
  display.println("by INOROBO");
  display.display();
  delay(2000);
  display.clearDisplay();
loading();
}

void loading(){
  display.clearDisplay();
  display.setTextSize(2);
   display.setCursor(5, 0);      //Draw the coordinate (x,y);
   display.println("REMOTE RC");
   display.setCursor(10, 24);
   display.print("loading..");
   display.display();
   delay(500);
}
