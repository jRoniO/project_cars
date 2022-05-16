// Include the servo library:
#include <Servo.h>
#include <OPT3101.h>
#include <Wire.h>


// Create a new servo object:
Servo myservo;

// Define the servo pin:
#define servoPin 5

const uint8_t dataReadyPin = 2; // Pin nummer för sensor läsning

int angle = 90; // Döper svängnings vinkel till angle

int leftsensor = 0;
int middlesensor = 1;
int rightsensor = 2;


// Namn för olika sväng vinklar för lättare ändring av svängvinkel
int Straight = 80; // Döper rakt vinkel 
int TurnAngle = 40;
int TurnRight = Straight - TurnAngle; // Döper HögerSvängnings vinkel
int TurnLeft = Straight + TurnAngle; // Döper VänsterSvängnings vinkel 

// namn för avstånd mättning
int Near = 200;
int NotSafe = 350;
int Safe = 600;

OPT3101 sensor;   // döper sensorn
int16_t distances[3]; // aktiverar tre punkter på sensor och döper de till distances
volatile bool dataReady = false;
void setDataReadyFlag()
{
  dataReady = true;
}
