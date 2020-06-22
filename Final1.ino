//Open Serial Monitor to View the current mode and password status
//There is no emoji drawings implemented in the emoji mode but when a correct password is entered the numeric mode changes to the emoji mode so, 
//I don't print either emojis nor numbers in the emoji mode, what is implemented in emoji mode is a unique sound for each emoji number.
//Entering the reverse password returns back to the numeric mode.

int emoji=0;
int numeric=1;
int melody[] = {3830,2400,3038,1864 ,2550, 1272 ,2028,3112,2864,3400,2550,1912,2272,1500,2028,3830,1912,3000,2564,1500,3272 };
long tempo = 10000;
int beats[]  = { 16,32 };
int pause = 1000;
int rest_count = 100; 

// Initialize core variables
int tone_ = 0;
int beat = 0;
long duration  = 0;
int speakerOut=11;
int r1 =1;
int r2=2;
int reset_pin=A5;
int keypad_row[5]={A0,A1,A2,A3,A4};
int col_set[4]={6,7,8,9};
int row_set[4]={0,12,4,5};
int s=0;
int code[4]={1,2,1,2};
int password[4]={1,2,3,4};
int entered[100];
int set=10;
int combinations[][4]={{0,0,0,1},{0,0,1,0},{0,0,1,1},{0,1,0,0},{0,1,0,1},{0,1,1,0},{0,1,1,1},{1,0,0,0},{1,0,0,1},{1,1,0,0}};
int x=-1;
int num1=-1;int num2=-1;
void setup() {
for(int i=0;i<4;i++)
{pinMode(row_set[i], OUTPUT);
pinMode(col_set[i], OUTPUT);}
pinMode(speakerOut, OUTPUT);
for(int i=0;i<5;i++)
{pinMode(keypad_row[i], INPUT_PULLUP);}
//attachInterrupt(digitalPinToInterrupt(pin), ISR, mode);
pinMode(1,OUTPUT);
pinMode(2,OUTPUT);
pinMode(13,OUTPUT);
//pinMode(3,INPUT);
pinMode(reset_pin,OUTPUT);
pinMode(set,OUTPUT);

Serial.begin(9600);
}
void sound(int s1,int length_,int b)
{
  {for(int i=s1;i<(s1+length_);i++)

{
    tone_ = melody[i];
    beat = beats[b];

    duration = beat * tempo; // Set up timing

    playTone();
    // A pause between notes...
    delayMicroseconds(pause);}}
}
void playTone() {
  long elapsed_time = 0;
  if (tone_ > 0) { 
    while (elapsed_time < duration) {

      digitalWrite(speakerOut,HIGH);
      delayMicroseconds(tone_ / 2);
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 2);

      elapsed_time += (tone_);
    }
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);  
    }                                
  }                                
}
 
 void led(int r,int c)
{
   for (int i=0;i<4;i++)
  {digitalWrite(row_set[i],combinations[r][i]);}
   for(int k=0;k<4;k++)
    {digitalWrite(col_set[k],combinations[c][k]); }   
      digitalWrite(set,LOW);
delay(10);
  digitalWrite(set,HIGH);
  delay(10);
 for (int i=0;i<4;i++)
  {digitalWrite(row_set[i],LOW); }
   for(int k=0;k<4;k++)
    {digitalWrite(col_set[k],LOW); } 
      digitalWrite(set,LOW);
  }
  void ledr(int r,int c)
{
  
   for(int k=0;k<4;k++)
    {digitalWrite(col_set[k],combinations[c][k]); } 
     for (int i=0;i<4;i++)
  {digitalWrite(row_set[i],combinations[r][i]);}
      digitalWrite(set,LOW);
delay(10);
  digitalWrite(set,HIGH);
  delay(10);
 
   for(int k=0;k<4;k++)
    {digitalWrite(col_set[k],LOW); }
    for (int i=0;i<4;i++)
  {digitalWrite(row_set[i],LOW); }  
      digitalWrite(set,LOW);
  }

  
void col(int c)
{
   for(int i=0;i<10;i++)
   {
    led(i,c);
   }
    } 
    
void row(int r)
{
  
   for(int i=0;i<10;i++)
   {
    ledr(r,i);
   
    } 
    
     
  }

 

 
  


 
 void  selftesting_col()
  {
    for (int i=0;i<10;i++)
    {digitalWrite(reset_pin,0);
      col(i); 
     
      digitalWrite(reset_pin,1);
       delay(200);
       //Serial.println(millis());
 }
  }
   void  selftesting_row()
  {
    for (int i=0;i<10;i++)
    {digitalWrite(reset_pin,0);
 //   digitalWrite(set,1);
      row(i); 
      
   //    digitalWrite(set,0);
      digitalWrite(reset_pin,1);
       delay(200);
       //Serial.println(millis());
       }
  }


//////
int num0to4() {
  

 
 digitalWrite(r1, LOW);
   digitalWrite(r2, HIGH);


  if (digitalRead(keypad_row[0]) == LOW) {
    //Serial.println(i);
    return 0;
  }
 else if (digitalRead(keypad_row[1]) == LOW) 
 return 1;
  else if (digitalRead(keypad_row[2]) == LOW) 
 return 2;
 
  else if (digitalRead(keypad_row[3]) == LOW) 
 return 3;
  else if (digitalRead(keypad_row[4]) == LOW) 
 return 4;
 else return -1;
}

 int num5to9() {
 
 digitalWrite(r2, LOW);
   digitalWrite(r1, HIGH);
 if (digitalRead(keypad_row[0]) == LOW) {
    //Serial.println(i);
    return 5;
  }
 else if (digitalRead(keypad_row[1]) == LOW) 
 return 6;
  else if (digitalRead(keypad_row[2]) == LOW) 
 return 7;
 
  else if (digitalRead(keypad_row[3]) == LOW) 
 return 8;
  else if (digitalRead(keypad_row[4]) == LOW) 
 return 9;
 else return -1;
 
 }


 int keypadnum()
{
 num1= num0to4();

 num2=num5to9();
 if (num1!=-1)
 return num1;
 else if(num2!=-1)
 return num2;
 else return -1;
 
 }



 
void loop() {

digitalWrite(reset_pin,HIGH);
delay(200);
digitalWrite(reset_pin,LOW);
digitalWrite(13,LOW);
Serial.println("Selftesting columns");
selftesting_col();
Serial.println("Selftesting rows");
selftesting_row();
digitalWrite(13,HIGH);
int y=-1;
x=keypadnum();
delay(100);
s=0;
while(x==-1)
{ x=keypadnum();

if (x!=-1)
{////////////////NUMERIC MODE////////////////
   if(x==0 && numeric==1 && emoji==0 )
 {Serial.print("Drawing no.:");Serial.println(x);sound(0,3,0);
 draw_zero(); 
 entered[s]=x;check_password();change_password();  s=s+1;  x=keypadnum();}
 else if(x==1 && numeric==1 && emoji==0 )
 {Serial.print("Drawing no.:");Serial.println(x);sound(2,2,0);
 draw_one();
 entered[s]=x;check_password();change_password(); s=s+1; x=keypadnum();}
  else if(x==2 && numeric==1 && emoji==0 )
 {Serial.print("Drawing no.:");Serial.println(x);sound(4,3,1);
 draw_two();
 entered[s]=x;check_password();change_password(); s=s+1; x=keypadnum();}
  else if(x==3 && numeric==1 && emoji==0 )
 {Serial.print("Drawing no.:");Serial.println(x);sound(3,3,0);
 draw_three(); 
 entered[s]=x;check_password();change_password(); s=s+1; x=keypadnum();}
  else if(x==4 && numeric==1 && emoji==0 )
 {Serial.print("Drawing no.:");Serial.println(x);sound(5,3,1); 
 draw_four();
 entered[s]=x;check_password();change_password(); s=s+1; x=keypadnum();}
  else if(x==5 && numeric==1 && emoji==0 )
 {Serial.print("Drawing no.:");Serial.println(x);sound(7,3,1);
 draw_five(); 
 entered[s]=x;check_password();change_password(); s=s+1;x=keypadnum();}
  else if(x==6 && numeric==1 && emoji==0 )
 {Serial.print("Drawing no.:");Serial.println(x);sound(6,2,0);
 draw_six(); 
 entered[s]=x;check_password();change_password(); s=s+1;x=keypadnum();}
  else if(x==7 && numeric==1 && emoji==0 )
 {Serial.print("Drawing no.:");Serial.println(x);sound(8,2,1);
 draw_seven();
 entered[s]=x;check_password();change_password(); s=s+1; x=keypadnum();}
  else if(x==8 && numeric==1 && emoji==0 )
 {Serial.print("Drawing no.:");Serial.println(x);sound(1,2,1);
 draw_eight();
 entered[s]=x;check_password();change_password(); s=s+1;  x=keypadnum();}
  else if(x==9 && numeric==1 && emoji==0 )
 {Serial.print("Drawing no.:");Serial.println(x);sound(9,2,0);
 draw_nine();
 entered[s]=x;check_password();change_password(); s=s+1;  x=keypadnum();}



 /////////////EMOJI MODE///////////////////
  else if(x==0 && numeric==0 && emoji==1 )
 {Serial.print("emoji.:");Serial.println(x);sound(19,3,1);
 draw_emoji0(); 
 entered[s]=x;check_password();change_password();  s=s+1;  x=keypadnum();}
 else if(x==1 && numeric==0 && emoji==1  )
 {Serial.print("emoji.:");Serial.println(x);sound(20,3,0);
draw_emoji0();
 entered[s]=x;check_password();change_password(); s=s+1; x=keypadnum();}
  else if(x==2 && numeric==0 && emoji==1  )
 {Serial.print(" emoji.:");Serial.println(x);sound(18,2,1);
 draw_emoji0();
 entered[s]=x;check_password();change_password(); s=s+1; x=keypadnum();}
  else if(x==3 && numeric==0 && emoji==1  )
 {Serial.print(" emoji.:");Serial.println(x);sound(17,2,0);
draw_emoji0();
 entered[s]=x;check_password();change_password(); s=s+1; x=keypadnum();}
  else if(x==4 && numeric==0 && emoji==1 )
 {Serial.print(" emoji.:");Serial.println(x);sound(16,2,1); 
draw_emoji0();
 entered[s]=x;check_password();change_password(); s=s+1; x=keypadnum();}
  else if(x==5 && numeric==0 && emoji==1  )
 {Serial.print(" emoji:");Serial.println(x);sound(15,2,0);
draw_emoji0();
 entered[s]=x;check_password();change_password(); s=s+1;x=keypadnum();}
  else if(x==6 && numeric==0 && emoji==1  )
 {Serial.print(" emoji:");Serial.println(x);sound(14,3,1);
draw_emoji0();
 entered[s]=x;check_password();change_password(); s=s+1;x=keypadnum();}
  else if(x==7 && numeric==0 && emoji==1 )
 {Serial.print(" emoji:");Serial.println(x);sound(13,2,0);
draw_emoji0();
 entered[s]=x;check_password();change_password(); s=s+1; x=keypadnum();}
  else if(x==8 && numeric==0 && emoji==1  )
 {Serial.print(" emoji:");Serial.println(x);sound(12,3,1);
draw_emoji0();
 entered[s]=x;check_password();change_password(); s=s+1;  x=keypadnum();}
  else if(x==9 && numeric==0 && emoji==1  )
 {Serial.print(" emoji:");Serial.println(x);sound(11,2,0);
draw_emoji0();
 entered[s]=x;check_password();change_password(); s=s+1;  x=keypadnum();}
}
}}
  
void check_password()
{
back_to_numeric();
    if(password[0]==entered[s-3] && password[1]==entered[s-2]&& password[2]==entered[s-1] && password[3]==entered[s])
    {
      Serial.println("Correct password, Emojis Mode Activated");
      emoji=1;
      numeric=0;
     sound(0,6,1);
    }
  
   // else false;
}
 void back_to_numeric()
 {
  if(password[3]==entered[s-3] && password[2]==entered[s-2]&& password[1]==entered[s-1] && password[0]==entered[s])
    {
      Serial.println("Numeric Mode");
      //return true ; 
       emoji=0;
      numeric=1;
      sound(8,6,1);
      
    }
  
  } 
  void change_password()
  {
    if(code[0]==entered[s-7] && code[1]==entered[s-6]&& code[2]==entered[s-5] && code[3]==entered[s-4])
    {
      password[0]=entered[s-3];
      password[1]=entered[s-2];
      password[2]=entered[s-1];
      password[3]=entered[s];
      Serial.println("Changing Password to");
     Serial.print( password[0]);
     Serial.print( password[1]);
     Serial.print( password[2]);
     Serial.print( password[3]);
    }


    
  }
void draw_emoji0()
{
 

digitalWrite(reset_pin,HIGH);
delay(200);
digitalWrite(reset_pin,LOW);

  
  }
    

 void draw_emoji_1()
{
    digitalWrite(reset_pin,HIGH);
delay(200);
digitalWrite(reset_pin,LOW);
} 
  
  
 

void draw_zero()
{digitalWrite(reset_pin,HIGH);
delay(200);
digitalWrite(reset_pin,LOW);
 for(int i=0;i<10;i++)
  {led(i,0);
  delay(100);}
    for(int i=0;i<10;i++)
  {ledr(9,i);
  delay(100);
 
}
 for(int i=0;i<10;i++)
  {led(i,9);
  delay(100);}
   for(int i=0;i<10;i++)
  {ledr(0,i);
  delay(100);}
  
  
}
void draw_eight()
{digitalWrite(reset_pin,HIGH);
delay(200);
digitalWrite(reset_pin,LOW);
 for(int i=0;i<10;i++)
  {led(i,0);
  delay(100);}
   for(int i=0;i<10;i++)
  {ledr(0,i);
  delay(100);}
   for(int i=0;i<10;i++)
  {ledr(5,i);
  delay(100);}
   for(int i=0;i<10;i++)
  {led(i,9);
  delay(100);}
  for(int i=0;i<10;i++)
  {ledr(9,i);
  delay(100);}
}
void draw_seven()

{digitalWrite(reset_pin,HIGH);
delay(10);
digitalWrite(reset_pin,LOW);
for(int i=0;i<5;i++){
ledr(0,i);delay(100);}
for(int i=0;i<10;i++){
led(i,4);delay(100);}

for(int i=0;i<7;i++){
ledr(5,i);delay(100);}
}
void draw_three()

{digitalWrite(reset_pin,HIGH);
delay(10);
digitalWrite(reset_pin,LOW);
for(int i=0;i<5;i++){
ledr(0,i);delay(100);}
for(int i=0;i<5;i++){
led(i,5);delay(100);}

for(int i=0;i<5;i++){
ledr(5,i);delay(100);}
for(int i=5;i<9;i++){
led(i,5);delay(100);}

for(int i=0;i<6;i++){
ledr(9,i);delay(100);}}
void draw_four()

{digitalWrite(reset_pin,HIGH);
delay(10);
digitalWrite(reset_pin,LOW);

for(int i=0;i<10;i++){
led(i,6);delay(100);}

for(int i=0;i<7;i++){
ledr(6,i);delay(100);}
for(int i=0;i<7;i++){
led(i,0);delay(100);}
}
void draw_one()

{digitalWrite(reset_pin,HIGH);
delay(10);
digitalWrite(reset_pin,LOW);

for(int i=0;i<10;i++){
led(i,4);delay(100);}


}

 void draw_nine()
 {
  digitalWrite(reset_pin,HIGH);
delay(10);
digitalWrite(reset_pin,LOW);
for(int i=0;i<7;i++){
ledr(0,i);delay(100);}
for(int i=0;i<10;i++){
led(i,6);delay(100);}

for(int i=0;i<7;i++){
ledr(4,i);delay(100);}
for(int i=0;i<5;i++){
led(i,0);delay(100);
 }
 for(int i=0;i<7;i++){
ledr(9,i);delay(100);}}

void draw_five()
 {
 digitalWrite(reset_pin,HIGH);
 digitalWrite(set,LOW);
delay(10);
digitalWrite(reset_pin,LOW);


 
for(int i=0;i<6;i++){
led(i,0);


delay(100);}

   for(int i=6;i<9;i++){


 for(int k=0;k<4;k++)
    {digitalWrite(col_set[k],combinations[5][k]); } 
     for (int i=0;i<4;i++)
  {digitalWrite(row_set[i],combinations[2][i]);}
  delay(10);
      digitalWrite(set,LOW);
      led(i,5);
delay(100);



}
for(int i=0;i<6;i++)
   {
    ledr(5,i);
    delay(100);
    } 
      for(int i=0;i<6;i++)
   {
    led(0,i);
    delay(100);
    } 
for(int i=0;i<6;i++)
   {
    ledr(9,i);
    delay(100);
    } 
}
void draw_six()
{
digitalWrite(reset_pin,HIGH);
delay(10);
digitalWrite(reset_pin,LOW);

for(int i=6;i<9;i++){
led(i,5);


delay(100);}
 


for(int i=0;i<6;i++){
ledr(5,i);delay(100);}
 

delay(100);
  for(int i=0;i<10;i++){
led(i,0);delay(100);}

 for(int i=0;i<6;i++){
ledr(0,i);delay(100);}





for(int i=0;i<6;i++){
ledr(9,i);delay(100);}


}
  
void draw_two()
 {
  digitalWrite(reset_pin,HIGH);
delay(10);
digitalWrite(reset_pin,LOW);
for(int i=0;i<6;i++)
   {
    led(i,6);
    delay(100);
    } 
for(int i=0;i<6;i++)
   {
    ledr(0,i);
    delay(100);
    } 
for(int i=6;i<10;i++)
   {
    ledr(i,0);
    delay(100);
    } 
    
for(int i=0;i<6;i++)
   {
    ledr(5,i);
    delay(100);
    } 
for(int i=0;i<7;i++)
   {
    ledr(9,i);
    delay(100);
    } 



}
  
 


  
 
