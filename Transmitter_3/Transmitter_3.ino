#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

int pesan[2]={0,1};
const int tombol=2;
const int tombol2=3;
RF24 rf24(7,8);

const byte alamat = 225;

void setup() {
  pinMode(tombol,INPUT_PULLUP);
  pinMode(tombol2,INPUT_PULLUP);
  rf24.begin();
  rf24.openWritingPipe(alamat);
  rf24.setPALevel(RF24_PA_MAX);
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
  Serial.println(pesan[0]);
  rf24.write(pesan,4);
  delay(10);
}
