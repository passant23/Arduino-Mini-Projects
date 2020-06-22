// the elevator can save one order(pending) while moving or when the red led is on 
//this order is performed either while moving or afterwards depending on the current floor number




//interrupt is triggered when a switch or a key is pressed 
//the interrupt function saves the pressed switch/key




#include<Keypad.h>
#include <Stepper.h>
Stepper s(32,13,11,12,10);
int pending=-1;//to store requests in case of calls when "overweight" or when busy
int pending2=0;
int sevenseg [8][3]={{0,0,0},{ 0,0,1},{ 0,1,0}, {0,1,1}, {1,0,0}, {1,0,1} ,{1,1,0}, {1,1,1}};
int k;
int switchtime=0;
int currentfloor=0;
unsigned long currentmillis;
int weight;
bool overweight=false;
bool idle=true;
const byte rows = 4; //four rows
const byte cols = 2; //three columns
char keys[rows][cols] ={{'1','0'},{'3','2'},{'5','4'},{'7','6'}};
byte rowPins[rows] = {3, 4, 5,6}; //connect to the row pinouts of the keypad
byte colPins[cols] = {7, 8}; //connect to the column pinouts of the keypad
Keypad mykeypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

///////////////////////////////////////////////////////////////////////////////
//utility functions
/////////////////////////////////////////////////////////////////////////////////
int switchpressed(){
switchtime=switchtime+1;
int ss=currentmillis-switchtime;
//Serial.println(ss);
  if((digitalRead(0)||digitalRead(1)||digitalRead(A1)||digitalRead(9))&&((currentmillis-switchtime)>=200))
{ int q0= digitalRead(0); //lsb
  int q1= digitalRead(1);
  int q2= digitalRead(A1);
  int reqfloor=q2*4+q1*2+q0;
  
  return reqfloor;}
  else if(digitalRead(9)&&((currentmillis-switchtime)>=200))
  return 0;
  else
  return -1;
}
/////////////////////////////////////////////////////////////////////////////
void motion(int k)
{int p=k;
   if(currentfloor<p )
 {int c=currentfloor;

  for(int i=0;i<(p-c);i++)
  {
    s.step(-32);
 //

 //
  currentfloor=currentfloor+1;
 
  floornumber(currentfloor);
  
  //Serial.println(pending2);
  if(pending2==currentfloor)
  {wait1sec(); pending2=-1;}

  
  } 
  wait1sec();
if(pending2!=-1)
{pending=pending2;
  }


  

 }
 else if(currentfloor>p)
 {int c=currentfloor;
  for(int i=0;i<(c-p);i++)
  {s.step(32);

  //storeorders();
  currentfloor=currentfloor-1;
  floornumber(currentfloor);
   if(pending2==currentfloor)
  {wait1sec(); pending2=-1;}
  
  
  } 
  wait1sec();
if(pending2!=-1)
{pending=pending2;
  }
   }
}
//////////////////////////////////////////////////////////

///////////////////////////////////////////////////////
void floornumber(int num)
{ digitalWrite(A4,sevenseg[num][0]); //msb
  digitalWrite(A3,sevenseg[num][1]);
  digitalWrite(A2,sevenseg[num][2]);
}
//////////////////////////////////////////////////////

//////////////////////////////////////////////////////
void storeorders()
{
  char y= mykeypad.getKey();
   if(y!= NO_KEY){pending2=ReadKeypad(y);}
    else if(switchpressed()!=-1){pending2=switchpressed();}
    Serial.println(pending2);
   
    

}
//////////////////////////////////////////////////////////
void wait1sec()
{
  int t=millis();
  while(millis() < t+1000)
  {s.step(0);}
}
//////////////////////////////////////////////////////////
int ReadKeypad(char x)
{int key;
  //Serial.println(x);
key=x-48; //convert ascii to decimal
return key;}
///////////////////////////////////////////////////////////
void setup() {
s.setSpeed(60);
pinMode(A1,INPUT);
pinMode(1,INPUT);
pinMode(0,INPUT);
pinMode(A3,OUTPUT); //7 seg
pinMode(A4,OUTPUT); // 7 seg MSB
pinMode(A2,OUTPUT); //7 seg LSB
pinMode(A5,INPUT); //weight sensor
pinMode(A0,OUTPUT); //led
pinMode(2,INPUT); //interrupt pin
Serial.begin(9600);
attachInterrupt(digitalPinToInterrupt(2),storeorders,HIGH);

}
/////////////////////////////////////////////////////////////
void loop() {

    currentmillis=millis();
    
//------------checks weight--------------// if weight above 70 motor stops is taken 
int w = analogRead(A5);
  double volt = w* (5.0/ 1023.0);
  if(volt > 3.5)
  {
   digitalWrite(A0,HIGH);
  char y= mykeypad.getKey();
   if(y!= NO_KEY){pending=ReadKeypad(y);}
    else if(switchpressed()!=-1){pending=switchpressed();}
   }
   else {                              //if weight is less than 70 proceed
   {digitalWrite(A0,LOW);
   char y= mykeypad.getKey();
   if(y!= NO_KEY){pending=ReadKeypad(y);}
   else if(switchpressed()!=-1){pending=switchpressed();}
if(pending!=-1)
{motion(pending);
pending=-1;}
else if (pending2!=-1)
{motion(pending2);
pending2=-1;}
}

}
}
