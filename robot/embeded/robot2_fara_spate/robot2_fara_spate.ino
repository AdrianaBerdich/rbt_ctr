#include <SoftwareSerial.h>

#define KD 1//0.2//0.5
#define KP 2  //3
#define KI 0.5//1//10

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
int dist1,dist2,dist3;
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

long microsecondsToCentimeters(long microseconds) 
{
  int sum =0;
  for ( int i=0; i< 10; i++)
  {
    sum += microseconds / 29 / 2;
    delayMicroseconds(2);
  }
  return sum/10;
}

int sonar1()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration1 = pulseIn(echoPin, HIGH);
 dist1 = microsecondsToCentimeters(duration1);
  return dist1;
}

int sonar2()
{
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
 dist2 = microsecondsToCentimeters(duration2);
  return dist2;
}

int sonar3()
{
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
 dist3 = microsecondsToCentimeters(duration3);
  return dist3;
}

void fata(int rpm)
{
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);
  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, rpm);
  analogWrite(enB, rpm);
}

void spate(int rpm)
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // turn on motor B
  digitalWrite(in4, HIGH);
  digitalWrite(in3, LOW);
  analogWrite(enA, rpm);
  analogWrite(enB, rpm);
}

void dreapta(int rpm)
{
  digitalWrite(in2, HIGH); 
  digitalWrite(in1, LOW); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, value);
  analogWrite(enB, 0);
}
void stanga( int rpm)
{
  digitalWrite(in2, HIGH); 
  digitalWrite(in1, LOW); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA,0);
  analogWrite(enB, value);
}
void stop()
{
  digitalWrite(in2, HIGH); 
  digitalWrite(in1, LOW); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void loop()
{
  sonar1();
  sonar2();
  sonar3();
 
  erroare =  dist2 - 20;
  correction = KP * erroare + (erroare_old + erroare) * KI +  (erroare_old - erroare) * KD;
  erroare_old = erroare;
  erroare_sum += erroare;
  value += correction;

  if(value < 0) //512
    {
      value = 0;
    }
    else
    if(value>300)
    {
      value=255 ; //542;
    }

  if( (dist2 < 40) && (dist1 > 40) && (dist3 > 40))
  {
      fata(value);  
  }
 /* if( (dist2 < 19) &&  (dist2 > 2) && (dist1 > 40) && (dist3 > 40))
  {
      spate(-value);
  }
  if( ((dist2 > 40 ) || (dist2 <2 ))&& (dist1 > 40) && (dist3 > 40))
  {
      stop(); 
  }
  if( (dist2 < 21 ) && (dist2 > 19 ) && (dist1 > 40) && (dist3 > 40))
  {
      stop(); 
  }
  */
  if (((dist2 > 40) && (dist1 < 25)&& (dist3 > 40)) || ((dist2 < 25) && (dist1 < 25) && (dist3 > 40)))
  {
    stanga(value);
  }
  if (((dist2 > 40) && (dist3 < 25)  && (dist1 > 40)) || ((dist2 < 25) && (dist3 < 25) && (dist1 > 40)))
  {
    dreapta(value);
  }
  
 
     Serial.println(dist1);
     Serial.println(dist2);
     Serial.println(dist3);
     Serial.println(erroare);
     Serial.println(correction);
     Serial.println(value);
     Serial.println("\n");
     
}

