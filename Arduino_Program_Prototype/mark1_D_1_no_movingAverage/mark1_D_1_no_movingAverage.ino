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

NexText t0 = NexText(hal0,3,"t0");
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
//Serial.begin(9600);
nexInit();

for(int i=0;i<10;i++){
pinMode(pin[i],INPUT_PULLUP);
}
delay(1000);
//page1.show();
}

void inisialisasi(){
while(inisial==0){
  t0.setText("Initialization");
progbar1=millis();
delay(1000);  
progbar2=millis();

bartot=progbar2-progbar1;
bartot=map(bartot,0,bartot,0,100);
while(bartot1<bartot){
bartot1=bartot1+1;
delay(50);
j0.setValue(bartot1);
t0.setText("Please wait...");
}
delay(1000);
page1.show();
inisial=1;
}
}

//MOVING AVERAGE
//moving average analog 1 >> linear actuator tilt
int pressurea;

float presMov1a[10];
float presJum1a;
char presCount1a;
char presSig1a = 0;
char presSig11a = 0;
float presRata1a;

float presMov2a[20];
float presJum2a;
char presCount2a;
char presSig2a = 0;
char presSig22a = 0;
float presRata2a;

float presMova[20];
float presJuma;
char presCounta;
char presSiga = 0;
float presRataa;

float tilt = 0;

//moving average analog 2 >> linear actuator nozzel
int pressureb;

float presMov1b[10];
float presJum1b;
char presCount1b;
char presSig1b = 0;
char presSig11b = 0;
float presRata1b;

float presMov2b[20];
float presJum2b;
char presCount2b;
char presSig2b = 0;
char presSig22b = 0;
float presRata2b;

float presMovb[20];
float presJumb;
char presCountb;
char presSigb = 0;
float presRatab;

float nozzel = 0;

//moving average analog 3 >> resin a
int pressurec;

float presMov1c[10];
float presJum1c;
char presCount1c;
char presSig1c = 0;
char presSig11c = 0;
float presRata1c;

float presMov2c[20];
float presJum2c;
char presCount2c;
char presSig2c = 0;
char presSig22c = 0;
float presRata2c;

float presMovc[20];
float presJumc;
char presCountc;
char presSigc = 0;
float presRatac;

float resin_a = 0;

//moving average analog 4 >> resin b1
int pressured;

float presMov1d[10];
float presJum1d;
char presCount1d;
char presSig1d = 0;
char presSig11d = 0;
float presRata1d;

float presMov2d[20];
float presJum2d;
char presCount2d;
char presSig2d = 0;
char presSig22d = 0;
float presRata2d;

float presMovd[20];
float presJumd;
char presCountd;
char presSigd = 0;
float presRatad;

float resin_b1 = 0;

//moving average analog 5 >> resin b2
int pressuree;

float presMov1e[10];
float presJum1e;
char presCount1e;
char presSig1e = 0;
char presSig11e = 0;
float presRata1e;

float presMov2e[20];
float presJum2e;
char presCount2e;
char presSig2e = 0;
char presSig22e = 0;
float presRata2e;

float presMove[20];
float presJume;
char presCounte;
char presSige = 0;
float presRatae;

float resin_b2 = 0;

void loop() {
inisialisasi();
//Read analog pin



/*
//CALCULATE MOVING AVERAGE
//ANALOG 1
pressurea = analogRead(A0);
  
 
  presJuma = presJuma - presMova[presCounta];
  presMova[presCounta] = pressurea;
  presJuma = presJuma+presMova[presCounta];
  presCounta++;
  if(presCounta<2 && presSiga == 1){
    presRataa = presJuma/2; 
  }else{
    if(presCounta<2 && presSiga == 0){
    presRataa = presJuma/presCounta; 
  }
  }
  if(presCounta>=2){
    presCounta = 0;
    presSiga = 1;
    presSig1a = 1;
  }

//Level 1
if (presSig1a == 1){
  presJum1a = presJum1a - presMov1a[presCount1a];
  presMov1a[presCount1a] = presRataa;
  presJum1a = presJum1a+presMov1a[presCount1a];
  presCount1a++;
  if(presCount1a<2 && presSig11a == 1){
    presRata1a = presJum1a/2; 
  }else{
    if(presCount1a<2 && presSig11a == 0){
    presRata1a = presJum1a/presCount1a; 
  }
  }
  if(presCount1a>=2){
    presCount1a = 0;
    presSig11a = 1;
    presSig2a = 1;
  }
  presSig1a = 0;
}

//Level 2
if (presSig2a == 1){
  presJum2a = presJum2a - presMov2a[presCount2a];
  presMov2a[presCount2a] = presRata1a;
  presJum2a = presJum2a+presMov2a[presCount2a];
  presCount2a++;
  if(presCount2a<10 && presSig22a == 1){   //NILAINYA
    presRata2a = presJum2a/10; 
  }else{
    if(presCount2a<10 && presSig22a == 0){
    presRata2a = presJum2a/presCount2a; 
  }
  }
  if(presCount2a>=10){
    presCount2a = 0;
    presSig22a = 1;
  }
  presSig2a = 0;
}


//ANALOG 2
pressureb = analogRead(A2);
  
  presJumb = presJumb - presMovb[presCountb];
  presMovb[presCountb] = pressureb;
  presJumb = presJumb+presMovb[presCountb];
  presCountb++;
  if(presCountb<2 && presSigb == 1){
    presRatab = presJumb/2; 
  }else{
    if(presCountb<2 && presSigb == 0){
    presRatab = presJumb/presCountb; 
  }
  }
  if(presCountb>=2){
    presCountb = 0;
    presSigb = 1;
    presSig1b = 1;
  }

//Level 1
if (presSig1b == 1){
  presJum1b = presJum1b - presMov1b[presCount1b];
  presMov1b[presCount1b] = presRatab;
  presJum1b = presJum1b+presMov1b[presCount1b];
  presCount1b++;
  if(presCount1b<2 && presSig11b == 1){
    presRata1b = presJum1b/2; 
  }else{
    if(presCount1b<2 && presSig11b == 0){
    presRata1b = presJum1b/presCount1b; 
  }
  }
  if(presCount1b>=2){
    presCount1b = 0;
    presSig11b = 1;
    presSig2b = 1;
  }
  presSig1b = 0;
}

//Level 2
if (presSig2b == 1){
  presJum2b = presJum2b - presMov2b[presCount2b];
  presMov2b[presCount2b] = presRata1b;
  presJum2b = presJum2b+presMov2b[presCount2b];
  presCount2b++;
  if(presCount2b<10 && presSig22b == 1){
    presRata2b = presJum2b/10; 
  }else{
    if(presCount2b<10 && presSig22b == 0){
    presRata2b = presJum2b/presCount2b; 
  }
  }
  if(presCount2b>=10){
    presCount2b = 0;
    presSig22b = 1;
  }
  presSig2b = 0;
}

//ANALOG 3
  pressurec = analogRead(A4);
  
  presJumc = presJumc - presMovc[presCountc];
  presMovc[presCountc] = pressurec;
  presJumc = presJumc+presMovc[presCountc];
  presCountc++;
  if(presCountc<2 && presSigc == 1){
    presRatac = presJumc/2; 
  }else{
    if(presCountc<2 && presSigc == 0){
    presRatac = presJumc/presCountc; 
  }
  }
  if(presCountc>=2){
    presCountc = 0;
    presSigc = 1;
    presSig1c = 1;
  }

//Level 1
if (presSig1c == 1){
  presJum1c = presJum1c - presMov1c[presCount1c];
  presMov1c[presCount1c] = presRatac;
  presJum1c = presJum1c+presMov1c[presCount1c];
  presCount1c++;
  if(presCount1c<2 && presSig11c == 1){
    presRata1c = presJum1c/2; 
  }else{
    if(presCount1c<2 && presSig11c == 0){
    presRata1c = presJum1c/presCount1c; 
  }
  }
  if(presCount1c>=2){
    presCount1c = 0;
    presSig11c = 1;
    presSig2c = 1;
  }
  presSig1c = 0;
}

//Level 2
if (presSig2c == 1){
  presJum2c = presJum2c - presMov2c[presCount2c];
  presMov2c[presCount2c] = presRata1c;
  presJum2c = presJum2c+presMov2c[presCount2c];
  presCount2c++;
  if(presCount2c<10 && presSig22c == 1){
    presRata2c = presJum2c/10; 
  }else{
    if(presCount2c<10 && presSig22c == 0){
    presRata2c = presJum2c/presCount2c; 
  }
  }
  if(presCount2c>=10){
    presCount2c = 0;
    presSig22c = 1;
  }
  presSig2c = 0;
}

//ANALOG 4
 pressured = analogRead(A6);
  
  presJumd = presJumd - presMovd[presCountd];
  presMovd[presCountd] = pressured;
  presJumd = presJumd+presMovd[presCountd];
  presCountd++;
  if(presCountd<2 && presSigd == 1){
    presRatad = presJumd/2; 
  }else{
    if(presCountd<2 && presSigd == 0){
    presRatad = presJumd/presCountd; 
  }
  }
  if(presCountd>=2){
    presCountd = 0;
    presSigd = 1;
    presSig1d = 1;
  }

//Level 1
if (presSig1d == 1){
  presJum1d = presJum1d - presMov1d[presCount1d];
  presMov1d[presCount1d] = presRatad;
  presJum1d = presJum1d+presMov1d[presCount1d];
  presCount1d++;
  if(presCount1d<2 && presSig11d == 1){
    presRata1d = presJum1d/2; 
  }else{
    if(presCount1d<2 && presSig11d == 0){
    presRata1d = presJum1d/presCount1d; 
  }
  }
  if(presCount1d>=2){
    presCount1d = 0;
    presSig11d = 1;
    presSig2d = 1;
  }
  presSig1d = 0;
}

//Level 2
if (presSig2d == 1){
  presJum2d = presJum2d - presMov2d[presCount2d];
  presMov2d[presCount2d] = presRata1d;
  presJum2d = presJum2d+presMov2d[presCount2d];
  presCount2d++;
  if(presCount2d<10 && presSig22d == 1){
    presRata2d = presJum2d/10; 
  }else{
    if(presCount2d<10 && presSig22d == 0){
    presRata2d = presJum2d/presCount2d; 
  }
  }
  if(presCount2d>=10){
    presCount2d = 0;
    presSig22d = 1;
  }
  presSig2d = 0;
}


//ANALOG 5
 pressuree = analogRead(A8);
  
  presJume = presJume - presMove[presCounte];
  presMove[presCounte] = pressuree;
  presJume = presJume+presMove[presCounte];
  presCounte++;
  if(presCounte<2 && presSige == 1){
    presRatae = presJume/2; 
  }else{
    if(presCounte<2 && presSige == 0){
    presRatae = presJume/presCounte; 
  }
  }
  if(presCounte>=2){
    presCounte = 0;
    presSige = 1;
    presSig1e = 1;
  }

//Level 1
if (presSig1e == 1){
  presJum1e = presJum1e - presMov1e[presCount1e];
  presMov1e[presCount1e] = presRatae;
  presJum1e = presJum1e+presMov1e[presCount1e];
  presCount1e++;
  if(presCount1e<2 && presSig11e == 1){
    presRata1e = presJum1e/2; 
  }else{
    if(presCount1e<2 && presSig11e == 0){
    presRata1e = presJum1e/presCount1e; 
  }
  }
  if(presCount1e>=2){
    presCount1e = 0;
    presSig11e = 1;
    presSig2e = 1;
  }
  presSig1e = 0;
}

//Level 2
if (presSig2e == 1){
  presJum2e = presJum2e - presMov2e[presCount2e];
  presMov2e[presCount2e] = presRata1e;
  presJum2e = presJum2e+presMov2e[presCount2e];
  presCount2e++;
  if(presCount2e<10 && presSig22e == 1){
    presRata2e = presJum2e/10; 
  }else{
    if(presCount2e<10 && presSig22e == 0){
    presRata2e = presJum2e/presCount2e; 
  }
  }
  if(presCount2e>=10){
    presCount2e = 0;
    presSig22e = 1;
  }
  presSig2e = 0;
}

*/
pot=analogRead(A0)/10;
pot1=analogRead(A2)/10;
pot2=analogRead(A4)/10;
pot3=analogRead(A6)/10;
pot4=analogRead(A8)/10;

//show value function
n0.setValue(pot);     //variabel pot ditampilkan ke object "n0"
n1.setValue(pot1);
n2.setValue(pot2);
n3.setValue(pot3);
n4.setValue(pot4);
/*
n0.setValue(pot);     //variabel pot ditampilkan ke object "n0"
n1.setValue(pot1);
n2.setValue(pot2);
n3.setValue(pot3);
n4.setValue(pot4);


Serial.print(pot);
Serial.print(" ");
Serial.print(presRata2a);
Serial.print("//");
Serial.print(pot1);
Serial.print(" ");
Serial.print(presRata2b);
Serial.print("//");
Serial.print(pot2);
Serial.print(" ");
Serial.print(presRata2c);
Serial.print("//");
Serial.print(pot3);
Serial.print(" ");
Serial.print(presRata2d);
Serial.print("//");
Serial.print(pot4);
Serial.print(" ");
Serial.print(presRatae);
Serial.println("//");
/*
if(digitalRead(pin[0])==LOW){
t1.setText("START");
}

if(digitalRead(pin[0])==HIGH){
t1.setText("STOP");
}
*/

// BACA INDIKATOR TOMBOL
if( digitalRead(pin[0])==LOW && digitalRead(pin[1])==LOW && digitalRead(pin[2])==LOW ) { t1.setText("START"); t10.setText("-");}
if( digitalRead(pin[0])==HIGH && digitalRead(pin[1])==LOW && digitalRead(pin[2])==LOW ) { t1.setText("RUNNING"); t10.setText("HOME"); }
if( digitalRead(pin[0])==LOW && digitalRead(pin[1])==HIGH && digitalRead(pin[2])==LOW ) { t1.setText("RUNNING"); t10.setText("KANAN"); }
if( digitalRead(pin[0])==HIGH && digitalRead(pin[1])==HIGH && digitalRead(pin[2])==LOW ) { t1.setText("RUNNING"); t10.setText("KIRI"); }
if( digitalRead(pin[0])==LOW && digitalRead(pin[1])==LOW && digitalRead(pin[2])==HIGH ) { t1.setText("RUNNING"); t10.setText("EMERGENCY"); }
if( digitalRead(pin[0])==HIGH && digitalRead(pin[1])==LOW && digitalRead(pin[2])==HIGH ) { t1.setText("STOP"); t10.setText("PAUSE"); }
if( digitalRead(pin[0])==LOW && digitalRead(pin[1])==HIGH && digitalRead(pin[2])==HIGH ) { t1.setText("RUNNING"); t10.setText("TURUN"); }
if( digitalRead(pin[0])==HIGH && digitalRead(pin[1])==HIGH && digitalRead(pin[2])==HIGH ) { t1.setText("STOP"); t10.setText("-"); }





// BACA POSISI SENSOR
if( digitalRead(pin[3])==LOW && digitalRead(pin[4])==LOW && digitalRead(pin[5])==LOW) { posisi.setValue(0); }  //AWAL
if( digitalRead(pin[3])==HIGH && digitalRead(pin[4])==LOW && digitalRead(pin[5])==LOW) { posisi.setValue(700); } //1
if( digitalRead(pin[3])==LOW && digitalRead(pin[4])==HIGH && digitalRead(pin[5])==LOW) { posisi.setValue(600); } //2
if( digitalRead(pin[3])==HIGH && digitalRead(pin[4])==HIGH && digitalRead(pin[5])==LOW) { posisi.setValue(500); } //3
if( digitalRead(pin[3])==LOW && digitalRead(pin[4])==LOW && digitalRead(pin[5])==HIGH) { posisi.setValue(400); } //4
if( digitalRead(pin[3])==HIGH && digitalRead(pin[4])==LOW && digitalRead(pin[5])==HIGH) { posisi.setValue(300); } //5
if( digitalRead(pin[3])==LOW && digitalRead(pin[4])==HIGH && digitalRead(pin[5])==HIGH) { posisi.setValue(200); }//6
if( digitalRead(pin[3])==HIGH && digitalRead(pin[4])==HIGH && digitalRead(pin[5])==HIGH) { posisi.setValue(100); }//7

//BACA URUTAN PROSES
if( digitalRead(pin[6])==LOW && digitalRead(pin[7])==LOW && digitalRead(pin[8])==LOW && digitalRead(pin[9])==LOW) { t9.setText(" 0"); }
if( digitalRead(pin[6])==HIGH && digitalRead(pin[7])==LOW && digitalRead(pin[8])==LOW && digitalRead(pin[9])==LOW) { t9.setText(" 1"); }
if( digitalRead(pin[6])==LOW && digitalRead(pin[7])==HIGH && digitalRead(pin[8])==LOW && digitalRead(pin[9])==LOW) { t9.setText(" 2"); }
if( digitalRead(pin[6])==HIGH && digitalRead(pin[7])==HIGH && digitalRead(pin[8])==LOW && digitalRead(pin[9])==LOW) { t9.setText(" 3"); }
if( digitalRead(pin[6])==LOW && digitalRead(pin[7])==LOW && digitalRead(pin[8])==HIGH && digitalRead(pin[9])==LOW) { t9.setText(" 4"); }
if( digitalRead(pin[6])==HIGH && digitalRead(pin[7])==LOW && digitalRead(pin[8])==HIGH && digitalRead(pin[9])==LOW) { t9.setText(" 5"); }
if( digitalRead(pin[6])==LOW && digitalRead(pin[7])==HIGH && digitalRead(pin[8])==HIGH && digitalRead(pin[9])==LOW) { t9.setText(" 6"); }
if( digitalRead(pin[6])==HIGH && digitalRead(pin[7])==HIGH && digitalRead(pin[8])==HIGH && digitalRead(pin[9])==LOW) { t9.setText(" 7"); }
if( digitalRead(pin[6])==LOW && digitalRead(pin[7])==LOW && digitalRead(pin[8])==LOW && digitalRead(pin[9])==HIGH) { t9.setText(" 8"); }
if( digitalRead(pin[6])==HIGH && digitalRead(pin[7])==LOW && digitalRead(pin[8])==LOW && digitalRead(pin[9])==HIGH) { t9.setText(" 9"); }
if( digitalRead(pin[6])==LOW && digitalRead(pin[7])==HIGH && digitalRead(pin[8])==LOW && digitalRead(pin[9])==HIGH) { t9.setText(" 10"); }
if( digitalRead(pin[6])==HIGH && digitalRead(pin[7])==HIGH && digitalRead(pin[8])==LOW && digitalRead(pin[9])==HIGH) { t9.setText(" 11"); }
if( digitalRead(pin[6])==LOW && digitalRead(pin[7])==LOW && digitalRead(pin[8])==HIGH && digitalRead(pin[9])==HIGH) { t9.setText(" 12"); }
if( digitalRead(pin[6])==HIGH && digitalRead(pin[7])==LOW && digitalRead(pin[8])==HIGH && digitalRead(pin[9])==HIGH) { t9.setText(" 13"); }
if( digitalRead(pin[6])==LOW && digitalRead(pin[7])==HIGH && digitalRead(pin[8])==HIGH && digitalRead(pin[9])==HIGH) { t9.setText(" 14"); }
if( digitalRead(pin[6])==HIGH && digitalRead(pin[7])==HIGH && digitalRead(pin[8])==HIGH && digitalRead(pin[9])==HIGH){ t9.setText(" 15"); }



//delay(1);
}

/*
 FUNCTION
page1.show(); -> show page
t1.setText("Kurang kenceng"); ->set text(string bukan int)
n0.setValue(pot);     //variabel pot ditampilkan ke object "n0"

*/
