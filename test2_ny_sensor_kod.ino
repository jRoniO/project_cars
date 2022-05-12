
#include <Servo.h> // Blibiotek för servon

#define PWMA 3 // PWM
#define AIN1 4 // Motor
#define AIN2 A0 // Motor 
#define START A1 // Startmodul

int pot;
int out;

// constants won't change
const int ServoPin = 2; // Servo
const int TrigPin1 = 7; // Höger sensor fram
const int EchoPin1 = 8; // Höger sensor fram
const int TrigPin2 = 9; // Vänster sensor fram 
const int EchoPin2 = 10; // Vänster sesnsor fram
const int TrigPin3 = 6; // Höger sensor
const int EchoPin3 = 5; // Höger sensor
const int TrigPin4 = 11; // Vänster sensor
const int EchoPin4 = 12; // Vänster sesnsor

// Variabler som kommer att ändras
float duration_left_front, distance_cm_left_front;
float duration_right_front, distance_cm_right_front;
float duration_left, distance_cm_left;
float duration_right, distance_cm_right;

Servo myServo; // create servo object to control a servo
// Servoposition:
const int noSteer = 105; // Rakt
const int steerHardLeft = 60; // Max vänstersväng
const int steerLeft = 75; // Lätt vänstersväng
const int steerHardRight = 130; // Max högersväng
const int steerRight = 115; // Lätt högersväng

void setup() {
  Serial.begin (9600);       // initialize serial port
  pinMode(PWMA,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(TrigPin1, OUTPUT); // Sätter PIN till OUTPUT
  pinMode(EchoPin1, INPUT);  // Sätter PIN till INPUT
  pinMode(TrigPin2, OUTPUT); // Sätter PIN till OUTPUT
  pinMode(EchoPin2, INPUT);  // Sätter PIN till INPUT
  pinMode(TrigPin3, OUTPUT); // Sätter PIN till OUTPUT
  pinMode(EchoPin3, INPUT);  // Sätter PIN till INPUT
  pinMode(TrigPin4, OUTPUT); // Sätter PIN till OUTPUT
  pinMode(EchoPin4, INPUT);  // Sätter PIN till INPUT
  myServo.write(noSteer); // Sätter servots startposition till mitten
  myServo.attach(ServoPin); // Servo attach på servons PIN
}

void loop() 
{
  // Motor
  digitalWrite(AIN1,LOW); // Fram
  digitalWrite(AIN2,HIGH); // Bak
  analogWrite(PWMA, 100); // Hastighet

  // Höger sensor fram
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TrigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin1, LOW);
  // measure duration of pulse from ECHO pin
  duration_right_front = pulseIn(EchoPin1, HIGH);
  //
  distance_cm_right_front = (duration_right_front/2) / 29.1; // Gör om till cm

  // Vänster sensor fram
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TrigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin2, LOW);
  // measure duration of pulse from ECHO pin
  duration_left_front = pulseIn(EchoPin2, HIGH);
  //
  distance_cm_left_front = (duration_left_front/2) / 29.1; // Gör om till cm  

  // Höger sensor
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TrigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin3, LOW);
  // measure duration of pulse from ECHO pin
  duration_left_front = pulseIn(EchoPin3, HIGH);
  //
  distance_cm_right = (duration_right/2) / 29.1; // Gör om till cm  

  // Vänster sensor
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TrigPin4, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin4, LOW);
  // measure duration of pulse from ECHO pin
  duration_left_front = pulseIn(EchoPin4, HIGH);
  //
  distance_cm_left = (duration_left/2) / 29.1; // Gör om till cm  

  // Kod för hur sensorn + servon
  
  // Höger fram sensorn
  // Om höger fram sensorn är mindre än 15cm och mindre än båda vänster sensorerna, sväng vänster
  if((distance_cm_right_front < 15 && distance_cm_right_front > 1)&&(distance_cm_right_front < distance_cm_left_front)&&(distance_cm_right_front < distance_cm_left))
    myServo.write(steerHardLeft); // Sväng full höger

  // Vänster fram sensorn
  // Om vänster fram sensor är mindre än 15cm och mindre än båda höger sensor, sväng höger.  
  else if((distance_cm_left_front < 15 && distance_cm_left_front > 1)&&(distance_cm_right_front > distance_cm_left_front)&&(distance_cm_left_front < distance_cm_right))
    myServo.write(steerHardRight); // Sväng full vänster

  // Höger sensor
  // Om vänster fram sensor är mindre än 15cm och mindre än båda höger sensor, sväng höger.  
  else if((distance_cm_right < 15 && distance_cm_right > 1)&&(distance_cm_right < distance_cm_left_front)&&(distance_cm_right < distance_cm_left))
    myServo.write(steerHardLeft); // Sväng full vänster

  // Vänster sensor
  // Om vänster fram sensor är mindre än 15cm och mindre än båda höger sensor, sväng höger.  
  else if((distance_cm_left < 15 && distance_cm_left > 1)&&(distance_cm_left < distance_cm_right_front)&&(distance_cm_right < distance_cm_left))
    myServo.write(steerHardLeft); // Sväng full vänster

  // Backfunktion

  
  // Annars kör rakt.
  else
    myServo.write(noSteer);  // rotate servo motor to 0 degree

  // Seriell Monitor (Avkoda för att se bättre)
  Serial.print("distance right front: ");
  Serial.print(distance_cm_right_front);
  Serial.println(" cm");
  Serial.print("distance left front: ");
  Serial.print(distance_cm_left_front);
  Serial.println(" cm");
  Serial.print("distance right: ");
  Serial.print(distance_cm_right);
  Serial.println(" cm");
  Serial.print("distance left: ");
  Serial.print(distance_cm_left);
  Serial.println(" cm");

  delay(250);
  }
