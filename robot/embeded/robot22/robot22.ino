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
int in4 = 13;

#define trigPin 12 //1
#define echoPin 11
long timp=0, cm=0;
long timp1=0, cm1=0;

#define trigPin2 7 //3
#define echoPin2 6
long timp2=0, cm2=0;

#define trigPin3 15 //2
#define echoPin3 14
long timp3=0, cm3=0;
int dist1,dist2,dist3;
int erroare = 0;
int erroare_old = 0;
int erroare_sum = 0;
int valoare = 100;
int corectie = 0;

unsigned int counter = 0;
unsigned int counter1 = 0;
unsigned char rising_edge;

#define vs_l 2
#define vs_r 3

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

 // pinMode(vs_l, INPUT);
//  pinMode(vs_r, INPUT);

 // timer1();
}

/*void timer1()
{
  noInterrupts();           // disable all interrupts
 // TCCR1A = 0;
 // TCCR1B = 0;
  TCNT1 = 15625;   // preload timer 65536-16MHz/256/2Hz
  TCCR1B |= (1 << CS12) | (1<< CS10);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
}

ISR(TIMER1_OVF_vect)
{
  TCNT1=15625;
  
  int rotation = (counter/20);
  Serial.println(rotation, DEC);
  counter=0;
  int rotation1 = (counter1/20);
  Serial.println(rotation1, DEC);
  counter1=0;
  int vs = (rotation1+rotation)/2;
  Serial.println(vs, DEC);
}
*/
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

int sonar3()
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
  analogWrite(enA, valoare);
  analogWrite(enB, 0);
}
void stanga( int rpm)
{
  digitalWrite(in2, HIGH); 
  digitalWrite(in1, LOW); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA,0);
  analogWrite(enB, valoare);
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

  if( (dist2 > 21) &&  (dist2 < 40) && (dist1 > 40) && (dist3 > 40))
  {
      fata(valoare);  
  }
  else
  if( (dist2 < 19) &&  (dist2 > 2) && (dist1 > 40) && (dist3 > 40))
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
/*if(digitalRead(vs_r) == HIGH)
  {
    counter++;
    //Serial.println("counter");
   // Serial.println(counter);
  }
   if(digitalRead(vs_l) == HIGH)
  {
    counter1++;
    //Serial.println("counter");
   // Serial.println(counter);
  }
 
  */
  /*
     Serial.println("dist1");
     Serial.println(dist1);
     Serial.println("dist2");
     Serial.println(dist2);
     Serial.println("dist3");
     Serial.println(dist3);
     Serial.println(erroare);
     Serial.println(corectie);
     Serial.println(valoare);
     Serial.println("\n");
     
   */  
}

