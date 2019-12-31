#include <QTRSensors.h> 
#define Kp 0.025
#define Kd 2//( Note: Kp < Kd)
#define Ki 0
#define rM 200
#define lM 200
#define rB 150
#define lB 150
#define TIMEOUT 2000
#define push A6
  
    byte a=1;
    byte b=0;
    byte x=1;
    byte y=0;


QTRSensorsRC qtrrc((unsigned char[]) {A0,A1,A2,A3,A4,8,9,10,11,12},10,TIMEOUT,QTR_NO_EMITTER_PIN);
   unsigned int sensorValues[10]; 


void setup() {
  
    Serial.begin(9600);
    
     pinMode(2, OUTPUT);
     pinMode(3, OUTPUT);
     pinMode(4, OUTPUT);
     pinMode(5, OUTPUT);
     pinMode(6, OUTPUT);  
     pinMode(7, OUTPUT); 
     pinMode(13, OUTPUT);
    pinMode(push,INPUT);
    pinMode(A7,OUTPUT);
    int push=0;
     
     delay(500);
  digitalWrite(13, HIGH); 
    
  for (int i = 0; i < 250; i++)
    {   qtrrc.calibrate();   }
  digitalWrite(13, LOW);
     delay(100);
     }
  
  float le = 0; 
   float l,e,mS,rS,lS;




void loop() { 
    
    unsigned int sensors[10]; 
    l = qtrrc.readLine(sensors); 
    Serial.println(l);
    e = l - 4500;  
    
    mS = Kp * e + Kd * (e - le);
    le = e; 
    rS = rB + mS;
    lS = lB - mS; 
    a=1; b=0; x=1; y=0;
    
    if (rS>rM)  rS=rM;
    if (lS>lM)  lS=lM;
    if (rS<0)   rS=0;
    if (lS<0)   lS=0;
    if (l>8900)
       {a=0;  b=1;
       lS=lM; rS=rM;}
    if (l<100)
       {x=0;  y=1;
       rS=rM; lS=lM;}
       digitalWrite(4, a);
      digitalWrite(5, b);
      analogWrite(3, lS);
      digitalWrite(2, x);
      digitalWrite(7, y);
      analogWrite(6, rS);


   }
