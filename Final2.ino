//Open Serial Monitor to view the steps :)
int arm=6; int n=-1;
int sugar=9;int eggs=10;int vanilla=11;int flour=13;int angle=10; int low_period; int raspberry=7;int pineapple=8;
int num1=-1;int num2=-1;
int open_valve=500;
int close_valve=1500;
int oven=12;
int stepper[4][2]={ {1,0} , { 1,0 } , {0,1} , {0,1} };
int production_line_pins[2]={0,1};
int mixer[2]={4,5};
int speed_normal=12.5;
int speed_slow=24;
int cake_stand[2]={2,3};

void decorate(int num)
{
  if (num==1)
  {valve(arm,1250);
  Serial.println("Decoration 1");
   digitalWrite(raspberry,HIGH);
     stepper_on(cake_stand,1,100);
    
     delay(500);
     digitalWrite(raspberry,LOW);

     valve(arm,1000);
        digitalWrite(pineapple,HIGH);
     stepper_on(cake_stand,1,100);
  
     delay(500);
    
     digitalWrite(pineapple,LOW);
    }
  else if (num==2)
  {valve(arm,1250);
    Serial.println("Decoration 2");
    stepper_stand_2(raspberry);
    delay(500);
valve(arm,1000);

     stepper_stand_2(pineapple);
     
     }
  else if(num==3)

  {  Serial.println("Decoration 3");
    valve(arm,1250);
    stepper_stand_3(raspberry);
    
valve(arm,1750);
delay(600);
    digitalWrite(pineapple,HIGH);
    delay(200);
    digitalWrite(pineapple,LOW);
    }
  else if(num==4)
{
    Serial.println("Decoration 4");
   valve(arm,1250);
  stepper_stand_4();
  digitalWrite(raspberry,HIGH);
  valve(arm,2000);
  delay(200);
  stepper_on(cake_stand,1,100);
  valve(arm,1750);
  delay(500);
  digitalWrite(raspberry,LOW);
  }

  
}




void valve(int pin_no,int high_period)
{
  digitalWrite(pin_no, HIGH);
         delayMicroseconds(high_period);
         low_period = 2000 - high_period ;
         digitalWrite(pin_no, LOW);
         delayMicroseconds(low_period);
         delay (10); 
         
}
void stepper_off(int *x)
{
  for( int i =0 ; i<2 ; i++)
  { digitalWrite(x[i],0);}
}

void stepper_on(int*x,int rev,int speed)
{
  for(int r=0;r<rev;r++){// Serial.println(millis()); 
  for(int i=0;i<8;i++){
    delay(speed);
    
  for ( int k=0 ; k< 4 ; k++)
{
  for( int j=0 ; j<2 ; j++)
  {
 digitalWrite(x[j],stepper[k][j]);
 
  }
}}
  }
}


//
void stepper_stand_3(int flavor)
{
    
   for(int i=0;i<8;i++)
  {

  for ( int k=0 ; k< 4 ; k++)
{

for( int j=0 ; j<2 ; j++)
  {
 digitalWrite(cake_stand[j],stepper[k][j]);
 delay(10);
 if(flavor ==raspberry)
  {if (k%2==0 )
    {
      digitalWrite(raspberry,HIGH);
       delay(20);
    }
     else
    {
      digitalWrite(raspberry,LOW);
       delay(20);
    }
  
  }
  else {
    if(k%2==0)
    {
      digitalWrite(pineapple,LOW);
       delay(20);
    }
     else 
    {
      digitalWrite(pineapple,HIGH);
       delay(20);
    }
   
}}

}

  
  }
  digitalWrite(pineapple,LOW);
  }
////////////////////////
void stepper_stand_4()
{
    
   for(int i=0;i<8;i++)
  {

  for ( int k=0 ; k< 4 ; k++)
{

for( int j=0 ; j<2 ; j++)
  {
 digitalWrite(cake_stand[j],stepper[k][j]);
 delay(10);

  {if (k%2==0 )
    {
      digitalWrite(raspberry,HIGH);
      digitalWrite(pineapple,LOW);
       delay(20);
    }
     else
    {
      digitalWrite(raspberry,LOW);
      digitalWrite(pineapple,HIGH);
       delay(20);
    }
  
  }
  {
   
   
}}

}

  
  }
  digitalWrite(pineapple,LOW);
  }



/////////
void stepper_stand_2(int flavor)
{
    
   for(int i=0;i<8;i++)
  {

  for ( int k=0 ; k< 4 ; k++)
{

for( int j=0 ; j<2 ; j++)
  {
 digitalWrite(cake_stand[j],stepper[k][j]);
 delay(10);
 if(flavor ==raspberry)
  {if (i%2==0)
    {
      digitalWrite(raspberry,HIGH);
       delay(20);
    }
     else
    {
      digitalWrite(raspberry,LOW);
       delay(10);
    }
  
  }
  else {
    if(i%2==0)
    {
      digitalWrite(pineapple,LOW);
       delay(10);
    }
     else 
    {
      digitalWrite(pineapple,HIGH);
       delay(20);
    }
   
}}

}

  
  }
  digitalWrite(pineapple,LOW);
  }
  

//

//MAKING THE CAKE
void make_cake()
{
  //a 
  Serial.println("Egg valve opens");
  valve(eggs,open_valve);
  delay(500);
  valve(eggs,close_valve);
  //b
  stepper_on(mixer,5,speed_normal);
  stepper_off(mixer);
  delay(100);
  //c
  Serial.println("Vanilla valve opens");

 
  stepper_on(mixer,2,speed_normal);
   Serial.println(millis());
   valve(vanilla,open_valve);
   
  stepper_on(mixer,1,speed_normal);
 valve(vanilla,close_valve);
 Serial.println(millis());
 stepper_on(mixer,1,speed_normal);
 
 stepper_off(mixer);
 
  //d
  Serial.println("Sugar valve opens");
 Serial.println(millis());
  valve(sugar,open_valve);
   
  delay(200);
  valve(sugar,close_valve);
  Serial.println(millis());
  //e
   stepper_on(mixer,10,speed_normal);
  
  stepper_off(mixer);
  //f and g
    Serial.println("Mixing Flour");
  for(int i=0;i<3;i++)
  {delay(50);
    valve(flour,open_valve);
  delay(100);
  valve(flour,close_valve);
  
   stepper_on(mixer,4,speed_slow);
  
  stepper_off(mixer);
  
    }

  
}
void bake_cake()
{
  //a
  Serial.println("Production line stepper moves");
stepper_on(production_line_pins,1,100);
  

  //b
  Serial.println("Oven on");
digitalWrite(12,HIGH);
delay(1000);
digitalWrite(12,LOW);

  //c
   Serial.println("Production line stepper moves");
stepper_on(production_line_pins,1,100);
  

  //d
  
  delay(1000);
  
  }



//////
int check_key3or4() {
 
 digitalWrite(A2, LOW);
   digitalWrite(A3, HIGH);

  if (digitalRead(A5) == LOW) {
    Serial.println("3");
   //delay(1000);
    return 3;
 } 
 else if (digitalRead(A4) == LOW) {
    Serial.println("4");
   //delay(1000);
    return 4;
 }
 else return -1;}

 int check_key1or2() {
 
   digitalWrite(A3, LOW);
   digitalWrite(A2, HIGH);
  if (digitalRead(A5) == LOW) {
    Serial.println("1");
    return 1;
   //delay(1000);
  
 } 
 else if (digitalRead(A4) == LOW) {
    Serial.println("2");
  // delay(1000);
    return 2;
  
 
 }
 else return -1;}
//////////


void setup() {
  // put your setup code here, to run once:
  //keypad pins
pinMode(A5,INPUT_PULLUP);
pinMode(A4,INPUT_PULLUP);  
pinMode(A3,OUTPUT);
pinMode(A2,OUTPUT);
////////////////  
//servos
pinMode(sugar,OUTPUT);
pinMode(eggs,OUTPUT);
pinMode(vanilla,OUTPUT);
pinMode(flour,OUTPUT);
///////////////////////
pinMode(oven,OUTPUT); //led
pinMode(raspberry,OUTPUT);
pinMode(pineapple,OUTPUT);
pinMode(arm,OUTPUT);
for(int i=0;i<6;i++)
{pinMode(i,OUTPUT);}  //mixer & production line & cake stand pins

Serial.begin(9600);
}
int decorate_num()
{num1= check_key1or2();

 num2=check_key3or4();
 if (num1!=-1)
 return num1;
 else if(num2!=-1)
 return num2;
 else return -1;
 
  }

void loop() {
make_cake();
bake_cake(); 

while(n==-1)
{ n=decorate_num();
if (n!=-1)
{decorate(n);
n=-1;
break;}}
}
//
