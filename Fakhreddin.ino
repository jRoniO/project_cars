/* Servo motor with Arduino example code. Position and sweep. More info: https://www.makerguides.com/ */

// Include the servo library:
#include <Servo.h>
#include <OPT3101.h>
#include <Wire.h>

// Create a new servo object:
Servo myservo;

// Define the servo pin:
#define servoPin 5

const int IN1 = 7;
const int IN2 = 4;
const int ENA = 3;


const uint8_t dataReadyPin = 2;
OPT3101 sensor;
int16_t distances[3];
volatile bool dataReady = false;
void setDataReadyFlag()
{
  dataReady = true;
}

int angle = 90;
int Speed = 100;


void setup() 
{

  
  // Attach the Servo variable to a pin:
    pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (ENA, OUTPUT);
 


  myservo.attach(servoPin);
   Wire.begin();
Serial.begin(9600);
  // Wait for the serial port to be opened before printing
  // messages (only applies to boards with native USB).
  while (!Serial) {}

  sensor.init();
  if (sensor.getLastError())
  {
    Serial.print(F("Failed to initialize OPT3101: error "));
    Serial.println(sensor.getLastError());
    while (1) {}
  }
  sensor.setContinuousMode();
  sensor.enableDataReadyOutput(1);
  sensor.setFrameTiming(32);
  sensor.setChannel(OPT3101ChannelAutoSwitch);
  sensor.setBrightness(OPT3101Brightness::Adaptive);

  attachInterrupt(digitalPinToInterrupt(dataReadyPin), setDataReadyFlag, RISING);
  sensor.enableTimingGenerator();
  
}

void loop() {

 

 //control speed 
  analogWrite(ENA, Speed); 
  
 if (dataReady)
  {
    sensor.readOutputRegs();
    distances[sensor.channelUsed] = sensor.distanceMillimeters;
      
       if (distances[1]<25) // Bilen backar om den är nära vägen 
       {
        Speed = 130;
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
         
       }
      else if (distances[1]>25 && distances[1]<150) // Bilen kör framåt men långsamt om den närmar sig väggen
       {
        Speed = 130;
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
       }
       else // Bilen kör framåt
       {
        Speed = 175;
         digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
       }

  if (Speed == 100) //back svängning
  
  {
    if (distances[0]<100)
       {
        myservo.write(60);
       }
       else if (distances[2]<100) 
       myservo.write(135);
  }

      else if (Speed > 100) // Bilen kör framåt ochsvänger rätt
      {
   if (sensor.channelUsed == 2)
    {
       if (distances[0]<400)
       {
        myservo.write(135);
       }
       else if (distances[2]<400) myservo.write(60);
       
       else myservo.write(90);
       
  // Skriver ut sensor data:
  
        Serial.print("\n");
        Serial.print("left sensor= ");
        Serial.print(distances[0]);
        Serial.print("\n");
  
        Serial.print("Middle Sensor= ");
        Serial.print(distances[1]);
        Serial.print("\n");
   
        Serial.print("Right Sensor= ");
        Serial.print(distances[2]);
       Serial.print("\n");
   
      Serial.println();
    }
    dataReady = false;
  }
  }
 

 
 

}
