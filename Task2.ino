#include <Stepper.h>

  void fire()
  {  int stepsPerRevolution = 32; 
     Stepper sfan(stepsPerRevolution, 8, 9, 10, 11);
     sfan.setSpeed(60);
     sfan.step(stepsPerRevolution);
     
  }
int tf=A5;
int tl=A3;
int tr=A1;
int efront=A4;
int eleft=A2;
int eright=A0;
int stepsPerRevolution = 32; 
double durationr,distancer,durationl,distancel,durationf,distancef;



void setup() 
{

pinMode(12,INPUT);
pinMode(13,INPUT);
pinMode(tf, OUTPUT); 
pinMode(tl, OUTPUT); 
pinMode(tr, OUTPUT);  
pinMode(efront ,INPUT); 
pinMode(eleft, INPUT);
pinMode(eright, INPUT);

attachInterrupt(digitalPinToInterrupt(12), fire, HIGH);

Serial.begin(9600);
}

void loop()
{ Stepper  sl(stepsPerRevolution,0,1,2,3);
  Stepper sr(stepsPerRevolution,4,5,6,7);
 
  sr.setSpeed(60);
sl.setSpeed(60);

  if (digitalRead(13)==HIGH)
  {       
  //FRONT
    digitalWrite(tf, LOW);
  delayMicroseconds(2);
  digitalWrite(tf, HIGH);
  delayMicroseconds(10);
  digitalWrite(tf, LOW);
  durationf = pulseIn(efront, HIGH);
  distancef= durationf*0.034/2;
   Serial.println(); 
  Serial.print("Front Distance: ");
  Serial.println(distancef);        
                 
//RIGHT
  digitalWrite(tr, LOW);
  delayMicroseconds(2);
  digitalWrite(tr, HIGH);
  delayMicroseconds(10);
  digitalWrite(tr, LOW);
  durationr = pulseIn(eright, HIGH);
  distancer= durationr*0.034/2;
  Serial.print("Right Distance: ");
  Serial.println(distancer);  


//LEFT
  digitalWrite(tl, LOW);
  delayMicroseconds(2);
  digitalWrite(tl, HIGH);
  delayMicroseconds(10);
  digitalWrite(tl, LOW);
  durationl = pulseIn(eleft, HIGH);
  distancel= durationl*0.034/2;
  Serial.print("Left Distance: ");
  Serial.println(distancel);  



 if(distancef > 250 )  //Check for front obstacles
     {
      for(int i=0;i<stepsPerRevolution;i++)
      {
        sr.step(1);
        sl.step(1);
      }
     }
else 
{
   if(distancer > 250 )  //Check for right obstacles
   { 
    for(int i=0;i<stepsPerRevolution;i++)
      {
        sr.step(1);
        sl.step(0);
      }
     
   }

   else if (distancel >250)  //Check for left obstacles
   {
     for(int i=0;i<stepsPerRevolution;i++)
      {
        sl.step(1);
        sr.step(0);
      }
     
   }
   else //backward
   {
    Stepper s1(stepsPerRevolution,3,2,1,0);
    Stepper sr(stepsPerRevolution,7,6,5,4);
    
    for(int i=0;i<stepsPerRevolution;i++)
      {
        sl.step(-1);
        sr.step(-1);
      }
 
   }
  
   
}

}

}


  
