#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
#include<EEPROM.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define pinBTN1 4
#define pinBTN2 2
#define pinBTN3 A3

byte BTN1,BTN2,BTN3;
byte pracon_F,wascon,con;
byte  tmr;  //timer reset
int tmradr;
byte mod_F,otp_F;
byte mainch=0;
byte subch=0;
byte otpch=0;
byte select=0;
float batval,batvalbuff1;

  String mainch_s="";
  String subch_s="";
  String otpch_s="";
  String pair="";

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
long int alamat =140130151;
long int alamat2=123234543;

void setup() {
pracon_F=1;
  display.setTextSize(1); // Draw 2X-scale text(1=7px, 2=14px it means 2 times from the pixel)
  display.setTextColor(WHITE);
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.clearDisplay();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    //Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
    display.display();
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(pinBTN1,INPUT_PULLUP);
  pinMode(pinBTN2,INPUT_PULLUP);
  pinMode(pinBTN3,INPUT_PULLUP);
  delay(100);
  //TESTING DEBUG
//  LOAD();
//  alamat=pair.toInt();
  rf24.begin();
  rf24.openReadingPipe(0, alamat);
  rf24.setPALevel(RF24_PA_MAX);
  rf24.startListening();
 //Serial.begin(9600);
  display.clearDisplay();
  wascon=0;
  con=0;
  tmr=0;
}

void loop() {
  readpin();
  setviewaddr();
  
  pracon();
  if(con==0) tmr=tmr+1;
  if(tmr>25) {
    wascon=0;
    tmr=0;
  }
  while (rf24.available()) {
    wascon=1;
    tmr=0;
    readpin();
    setviewaddr();
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
//    Serial.print("Masuk RF");
//    Serial.print(pesan[0]);
//    Serial.print(" ");
//    Serial.print(pesan[1]);
//    Serial.print(" ");
//    Serial.println(alamat);
    
  display.display();
  
  }
 con=0;
 
 
// Serial.print("Timer=");
// Serial.print(tmr);
//  Serial.print("    con=");
//  Serial.print(con);
//  Serial.print("  wascon=");
//  Serial.println(wascon);
  //Serial.println("ga masuk");
}

void mainscreen(){
  //display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);      //Draw the coordinate (x,y);
  display.println("Mobile RC");
  display.setCursor(0, 16);
  display.print("LVL");
  display.setCursor(60, 16);
 
}

void pracon(){
  display.clearDisplay();
  if(con==0 && wascon==0){
  display.setTextSize(1); // Draw 2X-scale text(1=7px, 2=14px it means 2 times from the pixel)
  display.setCursor(20, 0);
  display.print("DISCONNECTED");
  display.setCursor(0, 16);
  display.print("PRESS Button 3");
  display.setCursor(0, 24);
  display.print("To 'see' ADDR");
  display.setCursor(0, 38);
  display.print("PRESS & HOLD Button 3");
  display.setCursor(0, 46);
  display.print("To 'setting' ADDR");
  display.display();
  }


  if(con==0 && wascon==1){
    mainscreen();
    display.display();
  }
  


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
  display.println("SOCCER RC");
  display.setCursor(10, 24);
  display.print("loading..");
  display.display();
  delay(500);
}

void readpin(){
  BTN1=digitalRead(pinBTN1);
  BTN2=digitalRead(pinBTN2);
  BTN3=digitalRead(pinBTN3);
}

void setviewaddr(){
   if(BTN3==0){
  tmradr=0;
  checkaddr();
  while(BTN3==0){
    readpin();
    tmradr=tmradr+1;
    delay(1);
    if(tmradr>2000){
      setaddr();
    }
  }
  
 }
}
void checkaddr(){
  LOAD();
  display.setTextSize(2);
  display.clearDisplay();
  display.setCursor(5, 0);
  display.print("View ADDR");
  display.setCursor(2, 16);
  display.print(alamat);
  display.setCursor(2, 32);
  display.print(alamat2);
  display.setCursor(2, 48);
  display.print(pair);
  display.display();
  delay(700);
}

void setaddr(){
  mod_F=1;
  select=1;
  loading();
  LOAD();
  display.setTextSize(2);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("-SET ADDR-");
  while(mod_F==1){
    display.clearDisplay();
    readpin();
    if(BTN3==0){
      select=select+1;
      if(select>2) select=1;
      delay(200);
    }
    if(select==1){
      display.fillCircle(115,24,3,WHITE);
      if(BTN1==0){
        mainch=mainch+1;
        delay(10);
      }
       if(BTN2==0){
        mainch=mainch-1;
        delay(10);
      }

    }
    if(select==2){
      display.fillCircle(115,40,3,WHITE);
       if(BTN1==0){
        subch=subch+1;
        delay(10);
      }
       if(BTN2==0){
        subch=subch-1;
        delay(10);
      }

    }
  if(BTN3==0){
    tmradr=0;
    while(BTN3==0){
      readpin();
      tmradr=tmradr+1;
      delay(1);
      if(tmradr>1000){
        otp_F=1;
        OTP();
      }
    }
    tmradr=0;
  }
      
  display.setCursor(0, 0);
  display.print("-SET ADDR-");  
  display.setCursor(0, 16);
  display.print("MnCh:");
  display.print(mainch); //var main ch
  display.setCursor(0, 32);
  display.print("SbCh:");
  display.print(subch); //var sub ch
  display.display();
  delay(50);
  }
}

void OTP(){
  loading();
  display.setTextSize(2);
  display.clearDisplay();
  
  display.setCursor(0, 0);
  display.print("-SET OTP-");  
  while(otp_F==1){
    display.clearDisplay();
    readpin();
    if(BTN1==0){
      otpch=otpch+1;
      delay(10);
    }
    if(BTN2==0){
      otpch=otpch-1;
      delay(10);
    }
    if(BTN3==0){
    tmradr=0;
    while(BTN3==0){
      readpin();
      tmradr=tmradr+1;
      delay(1);
      if(tmradr>1000){

        display.clearDisplay();
        display.setCursor(7, 0);
        display.print("-SAVE-"); 
        display.display();
        delay(200);
        SAVE();
        display.clearDisplay();
        display.setCursor(7, 0);
        display.print("-LOAD-"); 
        display.display();
        delay(200);
        LOAD();
        display.clearDisplay();
        display.setCursor(7, 0);
        display.print("-CHANGE-"); 
        display.display();
        delay(200);
        changeaddr();

        mod_F=0;
        otp_F=0;
      }
    }
    tmradr=0;
  }
        display.setCursor(7, 0);
        display.print("-SET OTP-");  
        display.setCursor(10, 16);
        display.print("OTP CODE:");
        display.setCursor(45, 32);
        display.print(otpch);
        display.display();
  }
}


void LOAD() {
   
//  mainch=EEPROM.read(0);
//  subch=EEPROM.read(1);
//  otpch=EEPROM.read(2);
//EEPROM.get(0,mainch);
//EEPROM.get(1,subch);
//EEPROM.get(2,otpch);

  EEPROM.get(2,mainch);
  mainch_s=String(mainch);
  pair=mainch_s;
  EEPROM.get(3,subch);
  subch_s=String(subch);
  pair=mainch_s+subch_s;
  EEPROM.get(4,otpch);
  otpch_s=String(otpch);
  pair=mainch_s+subch_s+otpch_s;
  //pair="anying lah";
  
 //
}
void SAVE() {
  display.clearDisplay();
   display.setTextSize(2);
  display.setCursor(5, 0);
  display.print("-SET ADDR-");  
   display.setCursor(10, 24);
   display.print("Saving...");
   display.display();
  
  EEPROM.write(2, mainch);
  EEPROM.write(3, subch);
  EEPROM.write(4,otpch);
   delay(700);
}

void changeaddr(){
  alamat=pair.toInt();
  rf24.begin();
  rf24.openReadingPipe(0,alamat);
  rf24.setPALevel(RF24_PA_LOW);
  rf24.startListening();
  //delay(250);
}
