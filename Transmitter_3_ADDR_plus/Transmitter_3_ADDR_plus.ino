#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

int pesan[2]={0,1};
const int tombol=2;
const int tombol2=3;
RF24 rf24(9,10);  //def 7,8

//byte alamat ="INO1099";
//byte ino="ino";
int robo=9;
//byte alamat=ino+robo;
unsigned long alamat=123456789912345678991234567899;

void setup() {
  pinMode(tombol,INPUT_PULLUP);
  pinMode(tombol2,INPUT_PULLUP);
  rf24.begin();
  rf24.openWritingPipe(alamat);
  rf24.setPALevel(RF24_PA_LOW);
  rf24.stopListening();
  Serial.begin(9600);
}

void loop() {
  int bacaTombol,bacaTombol2;
  bacaTombol=digitalRead(tombol);
  bacaTombol2=digitalRead(tombol2);
  if(bacaTombol==0) pesan[0]={1};
  else if(bacaTombol2==0) pesan[0]={2};
  else if(bacaTombol==1 && bacaTombol2==1)pesan[0]={0};
  if(bacaTombol==0 && bacaTombol2==0) {
    pesan[0]={3};
   }
  //else if(bacaTombol2==0) pesan[0]={2};
  //else if(bacaTombol2==1) pesan[0]={3};
  
  //pesan[0]=bacaTombol;
    Serial.print(bacaTombol);
  Serial.print("  ");
  Serial.print(bacaTombol2);
  Serial.print("  ");
  Serial.print(pesan[0]);
   Serial.print("  ");
   Serial.print(alamat);
   Serial.print("  ");
   Serial.println(sizeof(alamat));
  rf24.write(pesan,4);
  delay(10);
}
