#include "Nextion.h"
byte hal0=0;
byte hal1=1;
byte hal2=2;
//          0,1, 2, 3,  4,5 , 6, 7, 8, 9,
int pin[]={32,34,36,38,40,42,44,64,19,18};  //pinnya dibalik
int progbar1=0;
int progbar2=0;
int inisial=0;
  
//Class variabel arduino=format(page,id,"objct name");
NexNumber n0 = NexNumber(hal1,1,"n0");
NexNumber n1 = NexNumber(hal1,7,"n1");
NexNumber n2 = NexNumber(hal1,9,"n2");
NexNumber n3 = NexNumber(hal1,10,"n3");
NexNumber n4 = NexNumber(hal1,13,"n4");

NexText t1 = NexText(hal1,2,"t1");
NexText t9 = NexText(hal1,17,"t9");
NexText t10 = NexText(hal1,18,"t10");

//NexPage page0 = NexPage(1, 0, "page0");
NexPage page1 = NexPage(1, 0, "page1");
NexPage opening=NexPage(0,0,"opening");
NexProgressBar j0 = NexProgressBar(0,2, "j0");

NexSlider posisi=NexSlider(hal1,14,"posisi");

//Variable declaration
int pot,pot1,pot2,pot3,pot4;
int bartot,bartot1;

void setup() {
nexSerial.begin(115200);
nexInit();

for(int i=0;i<10;i++){
pinMode(pin[i],INPUT_PULLUP);
}
delay(1000);
//page1.show();
}

void inisialisasi(){
while(inisial==0){
progbar1=millis();
delay(1000);  
progbar2=millis();

bartot=progbar2-progbar1;
bartot=map(bartot,0,bartot,0,100);
while(bartot1<bartot){
bartot1=bartot1+1;
delay(50);
j0.setValue(bartot1);
}
delay(1000);
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


//MOVING AVERAGE


//show value function
n0.setValue(pot);     //variabel pot ditampilkan ke object "n0"
n1.setValue(pot1);
n2.setValue(pot2);
n3.setValue(pot3);
n4.setValue(pot4);

if(digitalRead(pin[0])==LOW){
t1.setText("START");
}

else if(digitalRead(pin[0])==HIGH){
t1.setText("STOP");
}


// BACA INDIKATOR TOMBOL
else if( digitalRead(pin[1])==LOW && digitalRead(pin[2])==LOW ) { t10.setText("HOME"); }
else if( digitalRead(pin[1])==HIGH && digitalRead(pin[2])==LOW ) { t10.setText("KANAN"); }
else if( digitalRead(pin[1])==LOW && digitalRead(pin[2])==HIGH ) { t10.setText("KIRI"); }
else if( (digitalRead(pin[1])==HIGH) && (digitalRead(pin[2])==HIGH) ) { t10.setText("EMERGENCY"); }

// BACA POSISI SENSOR
else if( (digitalRead(pin[3])==LOW) && (digitalRead(pin[4])==LOW) && (digitalRead(pin[5])==LOW)) { posisi.setValue(7); }  //AWAL
else if( (digitalRead(pin[3])==HIGH) && (digitalRead(pin[4])==LOW) && (digitalRead(pin[5])==LOW)) { posisi.setValue(6); } //1
else if( (digitalRead(pin[3])==LOW) && (digitalRead(pin[4])==HIGH) && (digitalRead(pin[5])==LOW)) { posisi.setValue(5); } //2
else if( (digitalRead(pin[3])==HIGH) && (digitalRead(pin[4])==HIGH) && (digitalRead(pin[5])==LOW)) { posisi.setValue(4); } //3
else if( (digitalRead(pin[3])==LOW) && (digitalRead(pin[4])==LOW) && (digitalRead(pin[5])==HIGH)) { posisi.setValue(3); } //4
else if( (digitalRead(pin[3])==HIGH) && (digitalRead(pin[4])==LOW) && (digitalRead(pin[5])==HIGH)) { posisi.setValue(2); } //5
else if( (digitalRead(pin[3])==LOW) && (digitalRead(pin[4])==HIGH) && (digitalRead(pin[5])==HIGH)) { posisi.setValue(1); }//6
else if( (digitalRead(pin[3])==HIGH) && (digitalRead(pin[4])==HIGH) && (digitalRead(pin[5])==HIGH)) { posisi.setValue(0); }//7

//BACA URUTAN PROSES
else if( (digitalRead(pin[6])==LOW) && (digitalRead(pin[7])==LOW) && (digitalRead(pin[8])==LOW) && (digitalRead(pin[9])==LOW)) { t9.setText(" 16"); }
else if( (digitalRead(pin[6])==HIGH) && (digitalRead(pin[7])==LOW) && (digitalRead(pin[8])==LOW) && (digitalRead(pin[9])==LOW)) { t9.setText(" 15"); }
else if( (digitalRead(pin[6])==LOW) && (digitalRead(pin[7])==HIGH) && (digitalRead(pin[8])==LOW) && (digitalRead(pin[9])==LOW)) { t9.setText(" 14"); }
else if( (digitalRead(pin[6])==HIGH) && (digitalRead(pin[7])==HIGH) && (digitalRead(pin[8])==LOW) && (digitalRead(pin[9])==LOW)) { t9.setText(" 13"); }
else if( (digitalRead(pin[6])==LOW) && (digitalRead(pin[7])==LOW) && (digitalRead(pin[8])==HIGH) && (digitalRead(pin[9])==LOW)) { t9.setText(" 12"); }
else if( (digitalRead(pin[6])==HIGH) && (digitalRead(pin[7])==LOW) && (digitalRead(pin[8])==HIGH) && (digitalRead(pin[9])==LOW)) { t9.setText(" 11"); }
else if( (digitalRead(pin[6])==LOW) && (digitalRead(pin[7])==HIGH) && (digitalRead(pin[8])==HIGH) && (digitalRead(pin[9])==LOW)) { t9.setText(" 10"); }
else if( (digitalRead(pin[6])==HIGH) && (digitalRead(pin[7])==HIGH) && (digitalRead(pin[8])==HIGH) && (digitalRead(pin[9])==LOW)) { t9.setText(" 9"); }
else if( (digitalRead(pin[6])==LOW) && (digitalRead(pin[7])==LOW) && (digitalRead(pin[8])==LOW) && (digitalRead(pin[9])==HIGH)) { t9.setText(" 8"); }
else if( (digitalRead(pin[6])==HIGH) && (digitalRead(pin[7])==LOW) && (digitalRead(pin[8])==LOW) && (digitalRead(pin[9])==HIGH)) { t9.setText(" 7"); }
else if( (digitalRead(pin[6])==LOW) && (digitalRead(pin[7])==HIGH) && (digitalRead(pin[8])==LOW) && (digitalRead(pin[9])==HIGH)) { t9.setText(" 6"); }
else if( (digitalRead(pin[6])==HIGH) && (digitalRead(pin[7])==HIGH) && (digitalRead(pin[8])==LOW) && (digitalRead(pin[9])==HIGH)) { t9.setText(" 5"); }
else if( (digitalRead(pin[6])==LOW) && (digitalRead(pin[7])==LOW) && (digitalRead(pin[8])==HIGH) && (digitalRead(pin[9])==HIGH)) { t9.setText(" 4"); }
else if( (digitalRead(pin[6])==HIGH) && (digitalRead(pin[7])==LOW) && (digitalRead(pin[8])==HIGH) && (digitalRead(pin[9])==HIGH)) { t9.setText(" 3"); }
else if( (digitalRead(pin[6])==LOW) && (digitalRead(pin[7])==HIGH) && (digitalRead(pin[8])==HIGH) && (digitalRead(pin[9])==HIGH)) { t9.setText(" 2"); }
else if( (digitalRead(pin[6])==HIGH) && (digitalRead(pin[7])==HIGH) && (digitalRead(pin[8])==HIGH) && (digitalRead(pin[9])==HIGH)) { t9.setText(" 1"); }

else{}

delay(1);
}

/*
 FUNCTION
page1.show(); -> show page
t1.setText("Kurang kenceng"); ->set text(string bukan int)
n0.setValue(pot);     //variabel pot ditampilkan ke object "n0"

*/
