/*
* Bluetooh Basic: LED ON OFF - Avishkar
* Coder - Mayoogh Girish
* Website - http://bit.do/Avishkar
* Download the App : https://github.com/Mayoogh/Arduino-Bluetooth-Basic
* This program lets you to control a LED on pin 13 of arduino using a bluetooth module
*/
/*char data = 0;            //Variable for storing received data
void setup()
{
    Serial.begin(9600);   //Sets the baud for serial data transmission                               
    pinMode(13, OUTPUT);  //Sets digital pin 13 as output pin
}
void loop()
{
   if(Serial.available() > 0)      // Send data only when you receive data:
   {
      data = Serial.read();        //Read the incoming data & store into data
      Serial.print(data);          //Print Value inside data in Serial monitor
      Serial.print("\n");        
      if(data == '1')              // Checks whether value of data is equal to 1
         digitalWrite(13, HIGH);   //If value is 1 then LED turns ON
      else if(data == '0')         //  Checks whether value of data is equal to 0
         digitalWrite(13, LOW);    //If value is 0 then LED turns OFF
   }
}
void timerIsr(){
}
}*/
int enA=10;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 5;
int in3 = 4;
int in4 = 3;
void setup()
{
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}
void demoOne()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);
  delay(2000);
  // now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  delay(2000);
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void demoTwo()
{
  // this function will run the motors across the range of possible speeds
  // note that maximum speed is determined by the motor itself and the operating voltage
  // the PWM values sent by analogWrite() are fractions of the maximum speed possible 
  // by your hardware
  // turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  // accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  } 
  // decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  } 
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);  
}
void loop()
{
  demoOne();
  delay(1000);
 // demoTwo();
  delay(1000);
}

