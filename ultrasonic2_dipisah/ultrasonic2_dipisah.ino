long waktu1, jarak1;
long waktu2,jarak2;
long waktu3,jarak3;
void setup() {
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
pinMode(2,INPUT);
pinMode(3,INPUT);
pinMode(4,INPUT);
//attachInterrupt(digitalPinToInterrupt(2), sensor1, CHANGE);
//attachInterrupt(digitalPinToInterrupt(3), sensor2, CHANGE);
Serial.begin(115200);  
}



void loop() {

sensor1();
sensor2();
sensor3();

Serial.print("Sensor1=");
Serial.print(jarak1);
Serial.print(" CM      ");
Serial.print("Sensor2=");
Serial.print(jarak2);
Serial.print(" CM      ");
Serial.print("Sensor3=");
Serial.println(jarak3);

}

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
