// Include the servo library:
#include <Servo.h>
#include <OPT3101.h>
#include <Wire.h>


// Create a new servo object:
Servo myservo;

// Define the servo pin:
#define servoPin 5

const int IN1 = 7; // Pin nummer för motor 
const int IN2 = 4; // Pin nummer för motor 
const int ENA = 3; // Pin nummer för motors riktning

const uint8_t dataReadyPin = 2; // Pin nummer för sensor läsning

int angle = 90; // Döper svängnings vinkel till angle
int Speed = 100; // Döper hasigheten till Speed

int leftsensor = 0;
int middlesensor = 1;
int rightsensor = 2;

// Namn för olika hasigheter för lättare ändring av hastigheten.
int BackSpeed = 130;
int LowSpeed = 120;
int HighSpeed = 205;

// Namn för olika sväng vinklar för lättare ändring av svängvinkel
int TurnRight = 135; // Döper HögerSvängnings vinkel
int TurnLeft = 45; // Döper VänsterSvängnings vinkel 
int Straight = 90; // Döper rakt vinkel 

// namn för avstånd mättning
int Near = 15;
int NotSafe = 350;
int Safe = 500;


OPT3101 sensor;   // döper sensorn
int16_t distances[3]; // aktiverar tre punkter på sensor och döper de till distances
volatile bool dataReady = false;
void setDataReadyFlag()
{
  dataReady = true;
}
