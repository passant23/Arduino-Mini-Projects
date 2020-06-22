void setup() {
  // put your setup code here, to run once:
pinMode(0, INPUT);
pinMode(1, INPUT);
pinMode(2, INPUT);
pinMode(3, INPUT);

pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);


}

void loop() {

// each element in array c is one of the 16 combinations (7-bits with an extra 0-bit) of the truth table in decimal
// so at index 0, 126 corresponds to : 0 1111110 
// each bit corresponds to one of the seven segments (each segment has 3 leds)

  
int c[16]={126,06,109,121,51,91,95,112,127,123,119,31,78,61,79,71};
int dectobin[8] ; //array where the decimal no. will be converted to binary to use each bit as an output to the corresponding pin
int s0,s1,s2,s3; //switches
int index,pinvalues;
s0=digitalRead(0); //most significant 
s1=digitalRead(1);
s2=digitalRead(2);
s3=digitalRead(3);

index=8*s0 +4*s1+2*s2+s3; //uses s0,s1,s2,s3 to get the index of the array to get the corresponding combination 

pinvalues=c[index];
for (int i=0;i<9 ;i++)
{
dectobin[i]=bitRead(pinvalues,7-i); //bitRead function returns value of the the required bit therefore we can convert from decimal to binary.
}
digitalWrite(4,dectobin[1]);         
digitalWrite(5,dectobin[2]);
digitalWrite(6,dectobin[3]);
digitalWrite(9,dectobin[4]);
digitalWrite(10,dectobin[5]);
digitalWrite(7,dectobin[6]);
digitalWrite(8,dectobin[7]);


}
