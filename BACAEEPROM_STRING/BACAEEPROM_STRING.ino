#include<EEPROM.h>

//byte alamat[6]="ino123";
byte ino="123";
int robo=456;
int robox;
byte inorobo;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(2,INPUT_PULLUP);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int a=digitalRead(2);


if(a==0){
inorobo=ino+robo;
robox=255;
EEPROM.write(0,robox);
robo=EEPROM.read(0);
delay(1000);
}
Serial.print(ino);
Serial.print("  ");
Serial.print(robo);
Serial.print("  ");
Serial.println(inorobo);
}
