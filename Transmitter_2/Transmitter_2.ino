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
  rf24.setPALevel(RF24_PA_MIN);
  rf24.stopListening();
  Serial.begin(9600);
}

void loop() {
  int bacaTombol,bacaTombol2;
  bacaTombol=digitalRead(tombol);
  bacaTombol2=digitalRead(tombol2);
  pesan[0]=bacaTombol;
  pesan[1]=bacaTombol2;
  

//rf24.write(pesan,2);
  rf24.write(&bacaTombol,sizeof(bacaTombol));
  rf24.write(&bacaTombol2,sizeof(bacaTombol2));
  delay(10);
}
