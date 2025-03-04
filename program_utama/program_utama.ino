#include <Servo.h>
#define pinin1 3
#define pinin2 2
#define pinin3 5
#define pinin4 4
#define pinpompa 6
#define pintrigR 7
#define pinechoR 8
#define pintrigM 9
#define pinechoM 10
#define pintrigL 11
#define pinechoL 12
#define pinservo 13
#define pinL 14
#define pinR 15

#define batasjarak 30
 
Servo servo1;
long waktu1, jarak1;
long waktu2,jarak2;
long waktu3,jarak3;
int garisR,garisL;
void setup() {
pinMode(pinin1,OUTPUT);
pinMode(pinin2,OUTPUT);
pinMode(pinin3,OUTPUT);
pinMode(pinin4,OUTPUT);
pinMode(pinpompa,OUTPUT);
pinMode(pintrigR,OUTPUT);
pinMode(pinechoR,INPUT);
pinMode(pintrigM,OUTPUT);
pinMode(pinechoM,INPUT);
pinMode(pintrigL,OUTPUT);
pinMode(pinechoL,INPUT);
pinMode(pinL,INPUT);
pinMode(pinR,INPUT);

servo1.attach(pinservo);

inisialisasi();


//attachInterrupt(digitalPinToInterrupt(2), sensor1, CHANGE);
//attachInterrupt(digitalPinToInterrupt(3), sensor2, CHANGE);
Serial.begin(115200);  
}

/////////////////////////////////////////////
//DEKLARASI VOID

void trig(){
  digitalWrite(8,LOW);
delayMicroseconds(2);
digitalWrite(8,HIGH);
delayMicroseconds(10);
digitalWrite(8,LOW); 
}
void trig2(){
  digitalWrite(9,LOW);
delayMicroseconds(2);
digitalWrite(9,HIGH);
delayMicroseconds(10);
digitalWrite(9,LOW); 
}
void trig3(){
  digitalWrite(10,LOW);
delayMicroseconds(2);
digitalWrite(10,HIGH);
delayMicroseconds(10);
digitalWrite(10,LOW); 
}
void sensor1(){
  trig();
waktu1=pulseIn(2,HIGH);
jarak1=0.034/2*waktu1;
}

void sensor2(){
trig2();
waktu2=pulseIn(3,HIGH);
jarak2=0.034/2*waktu2; 
}

void sensor3(){
  trig3();
waktu3=pulseIn(4,HIGH);
jarak3=0.034/2*waktu3;
}


void inisialisasi(){
  servo1.write(90);
  analogWrite(pinin1,0);
  analogWrite(pinin2,0);
  analogWrite(pinin3,0);
  analogWrite(pinin4,0);
  analogWrite(pinpompa,0);
}

void STOP(){
    analogWrite(pinin1,0);
  digitalWrite(pinin2,LOW);
  analogWrite(pinin3,0);
  digitalWrite(pinin4,LOW);
 
}
void MAJU(){
    analogWrite(pinin1,255); //3
  digitalWrite(pinin2,LOW);     //2
  analogWrite(pinin3,255);     //5
  digitalWrite(pinin4,LOW);     //4 
}
void KANAN(){
    analogWrite(pinin1,0); //3
  digitalWrite(pinin2,LOW);     //2
  analogWrite(pinin3,255);     //5
  digitalWrite(pinin4,LOW);     //4 
}
void PUTARKANAN(){
    analogWrite(pinin1,0); //3
  digitalWrite(pinin2,HIGH);     //2
  analogWrite(pinin3,255);     //5
  digitalWrite(pinin4,LOW);     //4 
}
void KIRI(){
    analogWrite(pinin1,255); //3
  digitalWrite(pinin2,LOW);     //2
  analogWrite(pinin3,0);     //5
  digitalWrite(pinin4,LOW);     //4 
}
void PUTARKIRI(){
    analogWrite(pinin1,255); //3
  digitalWrite(pinin2,LOW);     //2
  analogWrite(pinin3,0);     //5
  digitalWrite(pinin4,HIGH);     //4 
}
void MUNDUR(){
    analogWrite(pinin1,0); //3
  digitalWrite(pinin2,HIGH);     //2
  analogWrite(pinin3,0);     //5
  digitalWrite(pinin4,HIGH);     //4 
}

void bacagaris(){
  garisL=digitalRead(pinL);
  garisR=digitalRead(pinR);
  if(garisL==0 && garisR==0){
    STOP();
  }
    if(garisL==1 && garisR==1){
    MAJU();
  }
    if(garisL==1 && garisR==0){
    KANAN();
  }
    if(garisL==0 && garisR==1){
    KIRI();
  }
  delay(50);
}

////////////////////////////////////////
void loop() {
bacagaris();
sensor1();
sensor2();
sensor3();
if(jarak1<batasjarak && jarak2>batasjarak && jarak3>batasjarak){
  STOP();
  delay(500);
  servo1.write(0);
  delay(500);
  analogWrite(pinpompa,255);
  delay(500);
  servo1.write(90);
  delay(200);
}
if(jarak1>batasjarak && jarak2<batasjarak && jarak3>batasjarak){
  STOP();
  delay(500);
  servo1.write(90);
  delay(500);
  analogWrite(pinpompa,255);
  delay(500);
  servo1.write(90);
  delay(200);
}

if(jarak1>batasjarak && jarak2>batasjarak && jarak3<batasjarak){
  STOP();
  delay(500);
  servo1.write(180);
  delay(500);
  analogWrite(pinpompa,255);
  delay(500);
  servo1.write(90);
  delay(200);
}


Serial.print("LEFT=");
Serial.print(garisL);
Serial.print("RIGHT=");
Serial.print(garisR);
Serial.print("    ");
Serial.print("Sensor1=");
Serial.print(jarak1);
Serial.print(" CM      ");
Serial.print("Sensor2=");
Serial.print(jarak2);
Serial.print(" CM      ");
Serial.print("Sensor3=");
Serial.println(jarak3);

}
