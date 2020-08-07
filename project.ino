#include <Servo.h>
Servo servo1;     // creating servo1 object
Servo servo2;     // creating servo2 object
Servo servo3;    // creating servo3 object
// defines variables
int sensorPin = 2;
int servoPin1 = 3;
int servoPin2 = 5;
int servoPin3 = 6;
int ledpin1 = 7;
int ledpin2 = 8;
int buzzer =11;
int person ;    // 
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance, sanitize,i,startPos;


void setup()
{
sanitize=0;
person = 0;
startPos = 0;
Serial.begin(9600);
servo1.attach(servoPin1); 
servo2.attach(servoPin2);
servo3.attach(servoPin3);
pinMode(sensorPin, INPUT); 
pinMode(ledpin1, OUTPUT); 
pinMode(ledpin2, OUTPUT); 
pinMode(buzzer, OUTPUT);  
pinMode(trigPin, OUTPUT);     // Sets the trigPin as an Output
pinMode(echoPin, INPUT);      // Sets the echoPin as an Input
}


void loop()
{ 
servo1.write(startPos);     //Setting all 3 motors to Initial position(0)
servo2.write(startPos);
servo3.write(startPos);
  
//Code to find the distance from ultrasonic sensor.
digitalWrite(trigPin, LOW);   // Clears the trigPin
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds
delayMicroseconds(10);
digitalWrite(trigPin, LOW);   // Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
distance= (duration*35)/1000; // Calculating the distance
distance= distance/2;
//Serial.println(distance);
  
person = digitalRead(sensorPin);   // Reading the PIR sensor and saving to the variable "person".
if (person == HIGH)                //If persons comes door will open through servo1 motor.
{
  Serial.println("Welcome...");
  servo1.write(180);                 //Rotating servo1 to open the main door.
  Serial.println("Door opening");
  delay(2000);}
else
{ 
  servo1.write(0);                  //Rotating servo1 to close the main door.
  delay(100);
}
                   
if (sanitize == 0)                 //If sanitization is not done then sensor starts to sense.
{
  Serial.println("Please stretch your hand..!! ");
  if(distance <50)                   //Sensing hand which is less than 50 cm.
  { 
    servo2.write(180);                 //Turning ON sanitizer motor for 3 seconds.
    delay(3000);    
    servo2.write(0);                   //Turning OFF sanitizer motor
    delay(100);
    Serial.println("Please take your hand out");    
    delay(3000);                                    //Waiting for person to take hand.
    sanitize=sanitize+1;      //Making 'sanitize' variable to 1 that person has done sanitization.
}  
}   
  else if (sanitize == 1)          //If and only if santization done goes inside the loop for opening pass gate.
{
    servo3.write(180);           //Turning ON pass gate motor.
    Serial.println("Pass gate opening");
    delay(3000);
    servo3.write(0);              //Turning OFF pass gate motor.
    Serial.println("Pass gate closing");
    digitalWrite(ledpin2, LOW);
    for (i=0;i<3;i++)           //Blinking green LED for 3 times.
   {
    digitalWrite(ledpin1, HIGH);
    delay(400);
    digitalWrite(ledpin1, LOW);
    delay(400);
   }
    tone(buzzer, 500);            //Beeping buzzer.
    delay(1000);
    noTone(buzzer);               //Turning OFF buzzer.
    digitalWrite(ledpin2, HIGH);  //Making red LED ON that indicates pass gate is closed.
    sanitize=0;                   //Clearing sanitize variable that sanitized person went inside.
 }
}
