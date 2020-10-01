#include<Servo.h>
int s1=1,s2=2,s3=3,s4=4,s5=5,s6=6,s7=7,s8=8;
int S1,S2,S3,S4,S5,S6,S7,S8;

void setup() {
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  pinMode(s4,OUTPUT);
  pinMode(s5,OUTPUT);
  pinMode(s6,OUTPUT);
  pinMode(s7,OUTPUT);
  pinMode(s8,OUTPUT);
  Serial.begin(9600);
  Servo.attach(13);
}

void loop() {
 S1= digitalRead(s1);
 S2= digitalRead(s2);
 S3= digitalRead(s3);
 S4= digitalRead(s4);
 S5= digitalRead(s5);
 S6= digitalRead(s6);
 S7= digitalRead(s7);
 S8= digitalRead(s8);

 if (S1==0)
 Serial.write("s1 high     ");
 
 if (S2==0)
 Serial.write("s2 high     ");
 
 if (S3==0)
 Serial.write("s3 high     ");
 
 if (S2==0)
 Serial.write("s4 high     ");
 
 if (S5==0)
 Serial.write("s5 high     ");
 
 if (S6==0)
 Serial.write("s6 high     ");
 
 if (S7==0)
 Serial.write("s7 high     ");
 
 if (S8==0)
 Serial.write("s8 high     ");


ultrasonic();
}

ultrasonic()
{
digitalWrite(trig,0);
delayMicroseconds(2);
digitalWrite(trig,1);
delayMicroseconds(10);
digitalWrite(trig,0);
t=pulseIn(echo,HIGH);
dist= (0.034/2)*t;
  if (dist>10)
  {
    for(i=0; i<=90; i++)
    {
      Servo.Write(i);
      delay(10);
      }
      for(i=90; i>=0; i--)
    {
      Servo.Write(i);
      delay(10);
      }
   }
}
