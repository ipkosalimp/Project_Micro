#include "Nextion.h"
#include "Arduino.h"
int hal1=1;
int pin[]={32,34,36,38,40,42,44};
int progbar1=0;
int progbar2=0;
int inisial=0;
int res1=0;
int res2=0;
int res3=0;

  
//Format variabel=format(page,id,"objct name");
NexNumber n0 = NexNumber(hal1,1,"n0");
NexNumber n1 = NexNumber(hal1,7,"n1");
NexNumber n2 = NexNumber(hal1,9,"n2");
NexNumber n3 = NexNumber(hal1,10,"n3");
NexNumber n4 = NexNumber(hal1,13,"n4");

NexText t1 = NexText(1,2,"t1");
//NexPage page0 = NexPage(1, 0, "page0");
NexPage page1 = NexPage(1, 0, "page1");
NexPage opening=NexPage(0,0,"opening");
NexProgressBar j0 = NexProgressBar(0,2, "j0");

//Variable declaration
int pot,pot1,pot2,pot3,pot4,pot5;
int bartot;
int bartot1=0;

void(* resetFunc) (void) = 0;

void setup() {

//Serial.begin(9600);
pinMode(3,OUTPUT);
pinMode(13,OUTPUT);
/*
for(int i=0;i<7;i++){
pinMode(pin[i],INPUT_PULLUP);
}
*/
pinMode(32,INPUT_PULLUP);
pinMode(34,INPUT_PULLUP);
pinMode(36,INPUT_PULLUP);
pinMode(38,INPUT_PULLUP);
pinMode(40,INPUT_PULLUP);
pinMode(42,INPUT_PULLUP);
pinMode(44,INPUT_PULLUP);

//digitalWrite(3,HIGH);
res1=millis();
 // resetFunc();

nexInit(); 

res2=millis();
res3=res2-res1;

if(res3>5000){
  digitalWrite(3,LOW);
  delay(500);
  resetFunc();
  digitalWrite(3,HIGH);
  }
//delay(1000);
nexSerial.begin(9600);

j0.setValue(bartot1);



 
 //page1.show();


//delay(1000);
//page1.show();
//Serial.println(res3);
}

void inisialisasi(){
while(inisial==0){
progbar1=millis();
delay(500);  
progbar2=millis();

bartot=progbar2-progbar1;
bartot=map(bartot,0,bartot,0,100);
while(bartot1<bartot){
bartot1=bartot1+1;
delay(50);
j0.setValue(bartot1);
}
delay(300);
page1.show();
inisial=1;
}
}

void loop() {
inisialisasi();
//Read analog pin
pot=analogRead(A0);
pot1=analogRead(A2);
pot2=analogRead(A4);
pot3=analogRead(A6);
pot4=analogRead(A8);
pot5=analogRead(A10);

//show value function
n0.setValue(pot);     //variabel pot ditampilkan ke object "n0"
n1.setValue(pot1);
n2.setValue(pot2);
n3.setValue(pot3);
n4.setValue(pot4);

if(digitalRead(pin[0])==LOW){
  //Serial.print("START");
t1.setText("START");
}
if(digitalRead(pin[0])==HIGH){
  //Serial.print("STOP");  
t1.setText("STOP");
}


//nexSerial.write(0xff);
//nexSerial.write(0xff);
//nexSerial.write(0xff);

//Serial.write(0xff);
//Serial.write(0xff);
//Serial.write(0xff);

delay(10);
}

/*
 FUNCTION
page1.show(); -> show page
t1.setText("Kurang kenceng"); ->set text(string bukan int)
n0.setValue(pot);     //variabel pot ditampilkan ke object "n0"

*/
