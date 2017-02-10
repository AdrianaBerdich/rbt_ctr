#include <SoftwareSerial.h>

#define KD 0.5//0.5
#define KP 3  //3
#define KI 2//10

char buffer[30];
char data = 0;

int enA=10;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 5;
int in3 = 4;
int in4 = 3;

#define trigPin 12 //1
#define echoPin 11
long duration=0, cm=0;
long duration1=0, cm1=0;

#define trigPin2 7 //3
#define echoPin2 6
long duration2=0, cm2=0;

#define trigPin3 13 //2
#define echoPin3 2
long duration3=0, cm3=0;
int distance1,distance2,distance3;
int erroare = 0;
int erroare_old = 0;
int erroare_sum = 0;
int value = 100;
int correction = 0;

void setup()
{
   Serial.begin(9600); 
   
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
 
}
void Fata()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);
  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 180);
  analogWrite(enB, 200);
}

void Stop()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
}

void Incetineste()
{
  // turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // decelerate from maximum speed to zero 
  for (int i = 100; i >= 0; --i)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  } 
  
}
void Stanga()
{
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 70);
  analogWrite(enB, 70);
}
void Dreapta()
{
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 70);
  analogWrite(enB, 70);
}
void Spate()
{
  digitalWrite(in2, LOW); 
  digitalWrite(in1, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, 100);
  analogWrite(enB, 100);
}
void Stopp()
{
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
long microsecondsToCentimeters(long microseconds) 
{
      return microseconds / 29 / 2;
}
/*void getDistValue()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
 
}
void getDistValue2()
{
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  cm2 = microsecondsToCentimeters(duration2);
 
}*/
int sonar1()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration1 = pulseIn(echoPin, HIGH);
 distance1 = microsecondsToCentimeters(duration1);
  return distance1;
}

int sonar2()
{
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
 distance2 = microsecondsToCentimeters(duration2);
  return distance2;
}

int sonar3()
{
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
 distance3 = microsecondsToCentimeters(duration3);
  return distance3;
}
void loop()
{
   sonar1();
    sonar3();
   sonar2();
  Serial.println(distance1);
   Serial.println(distance2);
    Serial.println(distance3);
     Serial.println("\n");
  if(distance2 <9)
  {
    Stop();
  }
  else if(distance2 >9)
  {
    Fata();
  }
  /*sonar1();
  sonar2();
  sonar3();
  if (distance2 <25 && distance2>14)
  {
    Fata();
  }
  if( distance2 < 14 && distance2>12)
  {
    Stopp();
  }
  if( distance2 < 12 && distance2 >2)
  {
    Spate();
  }
  if(distance2 > 25)
  {
    Stopp();
  }
  */
 /* Serial.println(distance1);
  Serial.println(distance2);
  Serial.println(distance3);
  Serial.println("\n");
  if(distance3>2)
  {
    while(distance2=0)
    {
      Stanga();
    }
  }
  
  if(distance1>2)
  {
    while(distance2=0)
    {
      Dreapta();
    }
  }
  
  if(distance1==0 && distance2==0 && distance3==0 )
    {
      Stop();
    }
  while(distance2>2)
  {
    Fata();
  }
  
*/
}

/*void loop()
{
 // Fata();
  getDistValue();
  getDistValue2();
 // Serial.println(duration);
 

  erroare =  cm - 20;
  correction = KP * erroare + (erroare_old + erroare) * KI +  (erroare_old - erroare) * KD;
  erroare_old = erroare;
  erroare_sum += erroare;
  value += correction;
  
  if(value<0) //512
    {
      value=0;
    }
    else
    if(value>255)
    {
      value=100; //542;
    }
    //sprintf(buffer, "%d,%d,%d,%d,", cm, erroare, correction, value);
   // printf("%d,%d,%d,%d", cm, erroare, correction, value);
    // Serial.println(buffer);
   //  Serial.println(erroare);
  //   Serial.println(correction);
    // Serial.println(value);
     //delay(500);
    // Serial.println("\n");
     //Serial.println(correction);
    // Serial.println(value);
   
 //  if (cm >21)
  //  {
   if ((cm > 20) && (cm2>20))
   { 
     digitalWrite(in2, HIGH);
     digitalWrite(in1, LOW);
     // turn on motor B
     digitalWrite(in3, HIGH);
     digitalWrite(in4, LOW);
     analogWrite(enA, value);
     analogWrite(enB, value);
   }
   if ((cm < 20) && (cm2<20))
   { 
     digitalWrite(in1, HIGH);
     digitalWrite(in2, LOW);
     // turn on motor B
     digitalWrite(in4, HIGH);
     digitalWrite(in3, LOW);
     analogWrite(enA, value);
     analogWrite(enB, value);
   }
/*    }
    else
    if (cm <19)
    {
     digitalWrite(in1, HIGH);
     digitalWrite(in2, LOW);
     // turn on motor B
     digitalWrite(in4, HIGH);
     digitalWrite(in3, LOW);
     analogWrite(enA, value);
     analogWrite(enB, value);
    }
    else
    {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);  
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
    }*/
/*    if ((cm > 20) && (cm2<20))//((cm > cm2) && (cm > 20)&&(cm2>20)) //Dreapta
    {
      digitalWrite(in2, HIGH); 
      digitalWrite(in1, LOW); 
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(enA, value);
      analogWrite(enB, 0);
    }
   // else
    if ((cm < 20) && (cm2>20))//((cm < cm2) && (cm > 20)&&(cm2>20))
    {
      digitalWrite(in2, HIGH); 
      digitalWrite(in1, LOW); 
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(enA,0);
      analogWrite(enB, value);
    }
    // Serial.println(cm);
    // Serial.println(cm2);
    // Serial.println("\n");
   //turatie(value);
}*/
