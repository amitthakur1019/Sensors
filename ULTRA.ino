#include <PS3BT.h>

#include <usbhub.h>
#include <NewPing.h>

#define TRIGGER_PIN1  36  
#define ECHO_PIN1     34 
#define MAX_DISTANCE1 200
#define TRIGGER_PIN2  32  
#define ECHO_PIN2     30  
#define MAX_DISTANCE2 200


NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE1); 
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE2); 
 
// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside nhnBTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
BTD Btd(&Usb);
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch
//PID
void pid();
int error;
int lasterror;
int errorsum;
int errordiff;
float val;
float kp=0.0;
float ki=0.0;
float kd=0.0;

int trigpin1 = 36;
int echopin1 = 34;
int trigpin2= 32;
int echopin2= 30;
float distance1;
float duration1;
float distance2;
float duration2;

void setup()
{
/*pinMode(trigpin1,OUTPUT);
pinMode(echopin1,INPUT);
pinMode(trigpin2,OUTPUT);
pinMode(echopin2,INPUT);*/
SerialUSB.begin(115200);

#if !defined(__MIPSEL__)
  while (!SerialUSB); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    SerialUSB.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  SerialUSB.print(F("\r\nPS3 Bluetooth Library Started"));


}

void loop()
{
Usb.Task();


  if (PS3.PS3Connected){
  //ultrasonicsensor1
  /*digitalWrite( trigpin1, LOW);
delayMicroseconds(2);
digitalWrite(trigpin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigpin1,LOW);
  duration1 = pulseIn(echopin1, HIGH);
  distance1 = (duration1*0.034)/2;

//ultrasonicsensor2
 
  digitalWrite( trigpin2, LOW);
delayMicroseconds(2);
digitalWrite(trigpin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigpin2,LOW);
  duration2 = pulseIn(echopin2, HIGH);
  distance2 = (duration2*0.034)/2;*/
distance1 = sonar1.ping_cm();
distance2 = sonar2.ping_cm();


//ULTRASONIC1
delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  SerialUSB.print("Ping1: ");
  SerialUSB.print(distance1); // Send ping, get distance in cm and print result (0 = outside set distance range)
  SerialUSB.print("cm        ");

//ULTRASONIC2
                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  SerialUSB.print("Ping2: ");
  SerialUSB.print(distance2); // Send ping, get distance in cm and print result (0 = outside set distance range)
  SerialUSB.println("cm");
 

 

 
  if( distance1 <15 || distance2<15 )
  {
      analogWrite(L1PWM, 0);
      analogWrite(R1PWM, 0);
      analogWrite(L2PWM, 0);
      analogWrite(R2PWM, 0);
      pid();
  }
  
  }
}

void pid()
{
  error = distance2 - distance3;
  errorsum = error + lasterror;
  errordiff = error - lasterror;
  val = kp*error + ki*errorsum + kd*errordiff;
  val = abs(val);
  if(error<0)
  {
     digitalWrite(L1DIR, 1);
      digitalWrite(L2DIR, 0);
      digitalWrite(R1DIR, 1);
      digitalWrite(R2DIR, 0);

      analogWrite(L1PWM, val);
      analogWrite(R1PWM, val);
      analogWrite(L2PWM, val);
      analogWrite(R2PWM, val);
   
  }
  if(error>0)
  {
     digitalWrite(L1DIR, 0);
      digitalWrite(L2DIR, 1);
      digitalWrite(R1DIR, 0);
      digitalWrite(R2DIR, 1);

      analogWrite(L1PWM, val);
      analogWrite(R1PWM, val);
      analogWrite(L2PWM, val);
      analogWrite(R2PWM, val);
   
  }
  if(error=0)
  {

      analogWrite(L1PWM, 0);
      analogWrite(R1PWM, 0);
      analogWrite(L2PWM, 0);
      analogWrite(R2PWM, 0);
  }
}
