#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

int pesan[2]={0,1};
RF24 rf24(7,8);  //def 7,8

//byte alamat ="INO1099";
//byte ino="ino";
int robo=300;
//byte alamat=ino+robo;
//long int alamat=1000;
long int alamat=140130150;

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
    rf24.read(pesan,2);
    if(pesan[0]==0){
      analogWrite(3,0);
      analogWrite(5,0);
      analogWrite(6,0);
    }else if(pesan[0]==1){
      analogWrite(3,255); //hijau
      analogWrite(5,0);  //merah
      analogWrite(6,0);  //biru
    }
    else if(pesan[0]==2){
      analogWrite(3,0);
      analogWrite(5,255);
      analogWrite(6,0);
    }
    else if(pesan[0]==3){
      analogWrite(3,0);
      analogWrite(5,0);
      analogWrite(6,255);
    }
     else if(pesan[0]==4){
      analogWrite(3,255);
      analogWrite(5,255);
      analogWrite(6,0);
    }
     else if(pesan[0]==5){
      analogWrite(3,255);
      analogWrite(5,0);
      analogWrite(6,255);
    }
     else if(pesan[0]==6){
      analogWrite(3,0);
      analogWrite(5,255);
      analogWrite(6,255);
    }
     else if(pesan[0]==7){
      analogWrite(3,255);
      analogWrite(5,0);
      analogWrite(6,0);
       
    }
     else if(pesan[0]==8){
      analogWrite(3,0);
      analogWrite(5,0);
      analogWrite(6,255);
      
    }
    
    delay(10);
    Serial.print("Masuk RF");
    Serial.print(pesan[0]);
    Serial.print(" ");
    Serial.print(pesan[1]);
    Serial.print(" ");
    Serial.println(alamat);
    
  }
//Serial.println("ga masuk");
}
