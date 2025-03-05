#include <modbus.h>
#include <modbusDevice.h>
#include <modbusRegBank.h>
#include <modbusSlave.h>


float pid;
float fc, RC;
float a, b;
float ef, ef_1;
float et, et_1;
float et_p;
float et_d;
float alpha;
float gamma;
float eint, eint_1, eint_update;
float edif,PVdif;
float Kp,Kp1,Kp2,Kpi, Ti,Ti1,Ti2,Tii, Td,Td1,Td2,Tdi, Ki, Kd;
float SV, PV,PV_1, sv1;
int MV;
int tipe;

unsigned long t;
double t_1, Ts;

float interval_elapsed;
float interval_limit;

int start;

int enA=6;


modbusDevice regBank;
modbusSlave slave;

void setup() {
//Konfigurasi PID
  Ts=0.001;
   fc=0.4;
    alpha=0.8;
    gamma=0.5; 
    RC=1/(6.28*fc);
    a=RC/Ts;
    b=a+1;
   
    
  et_1 = 0;
  eint_1 = 0;
   ef_1=0;
   
  interval_limit = 0.2;
  interval_elapsed = 0;

  t = millis();
  delay(100);

//System enable
  pinMode(8,INPUT);
  pinMode(10,OUTPUT);
  digitalWrite(10,HIGH);

//Konfigurasi motor
  pinMode(enA,OUTPUT);
  
  Serial.begin(9600);
  regBank.setId(1);

//arduino ke OPC
  regBank.add(30001);
  regBank.add(30002);
  regBank.add(30003);
  regBank.add(30004);
  regBank.add(30005);
  regBank.add(30006);

 //pid
 regBank.add(30021);
  regBank.add(30022);
  regBank.add(30023);
  regBank.add(30024);
  regBank.add(30025);
  regBank.add(30026);

//OPC ke Arduino
  regBank.add(40009);  
  regBank.add(40010); 
  //pid
  regBank.add(40021);
  regBank.add(40022);
  regBank.add(40023);
  regBank.add(40024);
  regBank.add(40025);
  regBank.add(40026);

  //tipe
  regBank.add(40028);
  
  slave._device = &regBank;  
  slave.setBaud(9600);  
 
}


void loop() {
    start=digitalRead(10);
         while (start == 1){
         man();
         SV=regBank.get(40010);
         PV=analogRead(A2)*0.004887;
         PV=PV*80;
         
          if (PV<0){
          PV=0;}
          else { PV=PV;} 
        slave.run();   
        tipe=regBank.get(40028);
       
        switch (tipe){ 
        case 1:
        pida();
        break;
        case 2:
        pidb();
        break;
        case 3:
        pidc();
        break;
        case 4:
        pidf();
        break;
        case 5:
        pidisa();
        break;
         default:
      break;
      }
    delay(10);
    tipe=tipe;  
    if (pid > 100){
      pid =100;
    }
    else if (pid < 0){
      pid = 0;
    }
    else {
      pid = pid;
    }
    
    pid=((pid/10)+10)/4;
    MV = pid*51;
    analogWrite(enA,MV);
        

    interval_elapsed = interval_elapsed + Ts;
    
    if (interval_elapsed >= interval_limit){
      interval_elapsed = 0;
    regBank.set(30001,(word)PV);
    regBank.set(30002,(word)MV);
    slave.run();
    }
    /*else{
      interval_elapsed = interval_elapsed;
    }  */
    interval_elapsed = interval_elapsed;
    et_1 = et;
    eint_1 = eint;
    t_1 = t;
    ef_1=ef;
    PV_1=PV;
    
    start=digitalRead(10);

           
    }
     
  
  analogWrite(enA,0);

  interval_elapsed = 0;

  et_1 = 0;
  eint_1 = 0;

  t = millis();
  delay (500);
  
    SV=regBank.get(40010);
         PV=analogRead(A1)*0.004887;
         PV=PV*80;
    
    if (PV < 0){
      PV = 0;}
    else { PV=PV;} 
     
      }



void man(){
  Kp=regBank.get(40021);
  Kp1=regBank.get(40022);
     Ti=regBank.get(40023);
     Ti1=regBank.get(40024);
     Td=regBank.get(40025);
     Td1=regBank.get(40026);
    Kp2=Kp1/1000;
    Td2=Td1/1000;
    Ti2=Ti1/1000; 
     Kpi=Kp+Kp2;
     Tii=Ti+Ti2;
     Tdi=Td+Td2;
      if (Tii == 0) {
       Ki = 0;
       }
       else {
       Ki = Kpi / Tii;
         }
      Kd=Kpi*Tdi;

    regBank.set(30021,(word)Kp);
    regBank.set(30022,(word)Kp2);
    regBank.set(30023,(word)Ti);
    regBank.set(30024,(word)Ti2);
    regBank.set(30025,(word)Td);
    regBank.set(30026,(word)Td2);
    slave.run();
}

void pida(){
         t_1 = t;
        t = millis();
        Ts=0.001;//(t - t_1)/1000;//0.01
    
        et = SV - PV;
    
        eint_update = ((et + et_1)*Ts)/2;
        eint = eint_1 + eint_update;
   
        edif = (et - et_1)/Ts;
    
         pid = Kpi*et + Ki*eint + Kd*edif;
    
  }




void pidb() {
 t_1 = t;
        t = millis();
        Ts=(t - t_1)/1000;//0.01
    
        et = SV - PV;
    
        eint_update = ((et + et_1)*Ts)/2;
        eint = eint_1 + eint_update;

        PVdif=(PV-PV_1)/Ts;
        //edif = (et - et_1)/Ts;
    
         pid = Kpi*et + Ki*eint - Kd*PVdif;
      }

void pidc(){
         t_1 = t;
        t = millis();
        Ts=(t - t_1)/1000;//0.01
    
        et = SV - PV;
    
        eint_update = ((et + et_1)*Ts)/2;
        eint = eint_1 + eint_update;
   
        PVdif=(PV-PV_1)/Ts;
    
         pid = Ki*eint - Kpi*PV - Kd*PVdif;
   }

void pidf(){
        t_1 = t;
        t = millis();
        Ts=(t - t_1)/1000;//0.01
    
        et = SV - PV;
    
        eint_update = ((et + et_1)*Ts)/2;
        eint = eint_1 + eint_update;

        ef = (et + a * ef_1) / b;
        edif = (ef - ef_1)/Ts;
    
        pid = Kpi*et + Ki*eint + Kd*edif;
    
  }

  void pidisa(){
         t_1 = t;
        t = millis();
        Ts=0.001;//(t - t_1)/1000;//0.01
    
        et = SV - PV;
        et_p=(SV*alpha)-PV;
        eint_update = ((et + et_1)*Ts)/2;
        eint = eint_1 + eint_update;
        et_d=(gamma*SV)-PV;
        ef = (et_d + a * ef_1) / b;
        edif = (ef - ef_1) / Ts;
         pid = Kpi*et_p + Ki*eint + Kd*edif;
    
  }

