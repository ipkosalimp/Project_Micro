#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

int pesan[2]={0,1};
RF24 rf24(7,8);

const byte alamat = 225;

void setup() {
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  delay(100);
  rf24.begin();
  rf24.openReadingPipe(0,alamat);
  rf24.setPALevel(RF24_PA_MIN);
  rf24.startListening();
Serial.begin(9600);
}

void loop() {
  while(rf24.available()){
    rf24.read(pesan,5);
    rf24.read(pesan[0],1);
    rf24.read(pesan[1],1);
    if(pesan[0]==0){
      analogWrite(3,255);
      analogWrite(5,0);
      analogWrite(6,0);
    }else if(pesan[0]==1){
      analogWrite(3,0);
      analogWrite(5,0);
      analogWrite(6,0);
    }
    else if(pesan[1]==0){
      analogWrite(3,0);
      analogWrite(5,255);
      analogWrite(6,0);
    }
    else if(pesan[1]==1){
      analogWrite(3,0);
      analogWrite(5,0);
      analogWrite(6,0);
    }
    delay(10);
    Serial.print("Masuk RF");
    Serial.print(pesan[0]);
    Serial.print(" ");
    Serial.println(pesan[1]);
  }
//Serial.println("ga masuk");
}
