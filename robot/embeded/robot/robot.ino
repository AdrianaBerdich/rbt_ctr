#include <SoftwareSerial.h>
#include <QTRSensors.h>
 
// software serial #1: RX = digital pin 10, TX = digital pin 11
SoftwareSerial portOne(10, 11);

// software serial #2: RX = digital pin 8, TX = digital pin 9
SoftwareSerial portTwo(8, 9);

char data = 0;

int enA=10;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 5;
int in3 = 4;
int in4 = 3;

int senzor_dreapta =14;
int senzor_stanga = 15;
int senzor_centru = 16;
int linie = 800;

QTRSensorsRC qtrrc((unsigned char[]) {14, 15, 16},
  3, 2500, 2); 
unsigned int sensorValues[3];

void setup()
{
   Serial.begin(9600); 
   while (!Serial) {
   // wait for serial port to connect. Needed for native USB port only
   }
   // Start each software serial port
   portOne.begin(9600);
   portTwo.begin(9600);
   
   
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
 
}
void Fata()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 80);
  analogWrite(enB, 100);
  // accelerate from zero to maximum speed
 /* for (int i = 0; i < 150; i++)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(200);
  }*/ 
  // now change motor directions
  /*digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  delay(2000);
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);*/
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
void Inainte()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 100);
  analogWrite(enB, 100);
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
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH);
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
void loop()
{
   //Serial.print(data);
  
  if(Serial.available() > 0)      // Send data only when you receive data:
   {
      data = Serial.read();        //Read the incoming data & store into data
      Serial.print(data);
      if (data == 'w')
      {
        //digitalWrite(13, HIGH);
        Fata();
        
      }
      if (data == 'd')
      {
        Stanga();
        delay(300);
        Fata();
        delay(8000);
      }
      if (data == 's')
      {
        //digitalWrite(13, LOW);
        Spate();
      }
      if ( data == 'a')
      {
        Dreapta();
      }
      if (data == 'q')
      {
        Stopp();
      }
   }

   /*
   if( senzor_centru > linie)
   {
    Dreapta();
   }
   else if(senzor_dreapta > linie)
   {
    Stanga();
   }
   else if(senzor_stanga > linie)
   {
    Dreapta();
   }
   if ((senzor_stanga > linie) && (senzor_centru > linie))
   {
    Stop();
   }
   else
   {
    Fata();
   }
   delay(0);
   */
}
   
 /*  qtrrc.read(sensorValues);

  // print the sensor values as numbers from 0 to 2500, where 0 means maximum reflectance and
  // 2500 means minimum reflectance
  for (unsigned char i = 0; i < 3; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
  }
  Serial.println();
  
  delay(250);
}*/
/*
void loop()
{
  if(Serial.available() > 0)      // Send data only when you receive data:
   {
      data = Serial.read();        //Read the incoming data & store into data
      Serial.print(data);          //Print Value inside data in Serial monitor
      Serial.print("\n");   
    if(data == 'w')              // Checks whether value of data is equal to 1
        { digitalWrite(13, HIGH);   //If value is 1 then LED turns ON
         Fata();
        }
      else if(data == 'a')         //  Checks whether value of data is equal to 0
         {digitalWrite(13, LOW);    //If value is 0 then LED turns OFF
         Stop();
         }
         else
         if(data =='s')
         Incetineste();
   }
}*/
       /*  if(data == 'w')  //fata
         {
          go(100, 100);
         }         
         if(data == 'a')//stanga
         {
          go(-100, 100);
         }
         if(data == 'd')  //dreapta
         {
          go(100, -100);
         }
         if(data == 's')  //spate
         {
          go(-100, -100);
         }         
         if(data == 'q')  //stop
         {
          go(0, 0);
         }                
   }*/
   /*
  portOne.listen();
  Serial.println("Data from port one:");
  // while there is data coming in, read it
  // and send to the hardware serial port:
  while (portOne.available() > 0) {
    char data1 = portOne.read();
    Serial.write(inByte);
    if(data1 == '1')              // Checks whether value of data is equal to 1
        { digitalWrite(13, HIGH);   //If value is 1 then LED turns ON
         Fata();
        }
      else if(data1 == '0')         //  Checks whether value of data is equal to 0
         {digitalWrite(13, LOW);    //If value is 0 then LED turns OFF
         Stop();
         }
         else
         if(data1 =='2')
         Incetineste();
  }

  // blank line to separate data from the two ports:
  Serial.println();

  // Now listen on the second port
  portTwo.listen();
  // while there is data coming in, read it
  // and send to the hardware serial port:
  Serial.println("Data from port two:");
  while (portTwo.available() > 0) {
    char inByte = portTwo.read();
    Serial.write(inByte);
  }

  // blank line to separate data from the two ports:
  Serial.println();
 */
 //}
