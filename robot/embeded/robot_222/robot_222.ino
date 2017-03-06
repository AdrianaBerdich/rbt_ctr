#include <SoftwareSerial.h>

//#define KD 0//0.2//0.5
//#define KP 9//2  //3
//#define KI 0//0.5//1//10
#define KD 1//0.2//0.5
#define KP 2  //3
#define KI 0.5//1//10

char buffer[30];
char data = 0;

int enA=6;//10;
int in1 = 9;
int in2 = 8;

int enB = 5;
int in3 = 4;
int in4 = 13;

#define trigPin 12 //1
#define echoPin 11
long timp=0, cm=0;
long timp1=0, cm1=0;

#define trigPin2 7 //3
#define echoPin2 10//6
long timp2=0, cm2=0;

#define trigPin3 14 //2
#define echoPin3 15
long timp3=0, cm3=0;
int dist1,dist2,dist3;
int dist_medie =0;
int dist_comp1, dist_comp2;
int erroare = 0;
int erroare_old = 0;
int erroare_sum = 0;
int valoare = 100;
int corectie = 0;
int val=0;

void setup()
{
   Serial.begin(9600); 
 
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
  timp1 = pulseIn(echoPin, HIGH);
  dist1 = microsecondsToCentimeters(timp1);
  return dist1;
}

int sonar2()
{
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  timp2 = pulseIn(echoPin2, HIGH);
  dist2 = microsecondsToCentimeters(timp2);
  return dist2;
}

int sonar3() // scos
{
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  timp3 = pulseIn(echoPin3, HIGH);
  dist3 = microsecondsToCentimeters(timp3);
  return dist3;
}

void fata(int rpm)
{
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, rpm);
  analogWrite(enB, rpm);
}

void spate(int rpm)
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
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
  analogWrite(enA, rpm);
  analogWrite(enB, 0);
}
void stanga( int rpm)
{
  digitalWrite(in2, HIGH); 
  digitalWrite(in1, LOW); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA,0);
  analogWrite(enB, rpm);
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
  dist_medie = (dist3 + dist2)/2;
 erroare =  dist2 - 20;
  corectie = KP * erroare + (erroare_old + erroare) * KI +  (erroare_old - erroare) * KD;
  erroare_old = erroare;
  erroare_sum += erroare;
  valoare += corectie;
  if (erroare ==0)
  {
    valoare =0;
  }
  else
  if(valoare<-200) //512
    {
      valoare=100;
    }
    else
    if(valoare>300)//200)
    {
      valoare=255;//100; //542;
    }

  if( (dist2 > 21) &&  (dist2 < 40) && (dist1 > 21) && (dist1< 40) && (dist3 > 21) && (dist3 < 40))
  {
      fata(valoare);  
  }
  else
  if( (dist2 < 19) &&  (dist2 > 2) && (dist1 < 19) && (dist3 < 19))
  {
      spate(-valoare);
  }
  else
  if( ((dist2 > 40 ) || (dist2 <2 ))&& (dist1 > 40) && (dist3 > 40))
  {
      stop(); 
  }
  else
  if( (dist2 < 21 ) && (dist2 > 19 ) && (dist1 > 40) && (dist3 > 40))
  {
      stop(); 
  }
  else
  if (((dist2 > 40) && (dist1 < 25) && (dist3 > 40)) || ((dist2 < 25) && (dist1 < 25) && (dist3 > 40)))
  {
    stanga(valoare);
  }
  else
  if (((dist2 > 40) && (dist3 < 25) && (dist1 > 40)) || ((dist2 < 25) && (dist3 < 25) && (dist1 > 40)))
  {
    dreapta(valoare);
  }
  else
  {
    stop();
  } 
/*  erroare = dist_medie - 20;
  corectie = KP * erroare + (erroare_old + erroare) * KI +  (erroare_old - erroare) * KD;
  erroare_old = erroare;
  erroare_sum += erroare;
  valoare += corectie;
  if (valoare <=0)
  {
    valoare =0;
  }
  else
    if(valoare>300)//200)
    {
      valoare=255;//100; //542;
    }

  dist_comp1 = dist3 + 1;
  dist_comp2 = dist3 - 1;
  if  ((dist2 >= dist_comp2) && (dist2 <= dist_comp1))
  {
     Serial.print("fata ");
    fata(valoare);
  }
  if((dist3>25) && (dist2 < 20) )//(dist3 < dist2) && ((dist3 >20)||(dist2 >20))) //stanga
  {
     Serial.print("stanga ");
    digitalWrite(in2, HIGH); 
    digitalWrite(in1, LOW); 
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, valoare);
    analogWrite(enA, 0);
  }
  if((dist3 < 25) && (dist2 > 20) )//( dist3 > dist2)&& ((dist3 >20)||(dist2 >20))) //dreapta
  {
     Serial.print("dreapta ");
     digitalWrite(in2, HIGH); 
     digitalWrite(in1, LOW); 
     digitalWrite(in3, HIGH);
     digitalWrite(in4, LOW);
     analogWrite(enB,0);
     analogWrite(enA, valoare);
  }*/

     Serial.println("dist1");
     Serial.println(dist1);
     Serial.print("dist2: ");
     Serial.println(dist2);
     Serial.print("dist3: ");
     Serial.println(dist3);
     Serial.print("erroare: ");
     Serial.println(erroare);
     Serial.print("corectie: ");
     Serial.println(corectie);
      Serial.print("valoare ");
     Serial.println(valoare);
     Serial.println("\n");
     
  
}

