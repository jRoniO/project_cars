#include "header.h"


void setup() 
{

  
  // Attach the Servo variable to a pin:
    pinMode (IN1, OUTPUT);
    pinMode (IN2, OUTPUT);
    pinMode (ENA, OUTPUT);
 


   myservo.attach(servoPin);
   myservo.write(90);
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

// Döper om sensorer
leftsensor = distances[0]; 
middlesensor = distances[1];
rightsensor = distances[2];


 //control speed 
  analogWrite(ENA, Speed); 
  
 if (dataReady)
  {
    sensor.readOutputRegs();
    distances[sensor.channelUsed] = sensor.distanceMillimeters;
      
       if (middlesensor<Near) // Bilen backar om den är nära vägen 
       {
        Speed = BackSpeed;
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        
         
       }
      else if (middlesensor>Near && middlesensor<NotSafe) // Bilen kör framåt men långsamt om den närmar sig väggen
       {
        Speed = map(middlesensor, Near, NotSafe, LowSpeed, HighSpeed);
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
       }
       else // Bilen kör framåt
       {
        Speed = HighSpeed;
         digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
       }

  
   if (sensor.channelUsed == 2)
    {
      if (Speed == BackSpeed) //back svängning
  
  {
    if (rightsensor<Near)
       {
          angle = map(rightsensor, NotSafe, Near, Straight, TurnLeft);
          myservo.write(angle); 
       }
       else if (leftsensor<Near) 
      {   
          angle = map(leftsensor, NotSafe, Near,  Straight, TurnRight);
          myservo.write(angle); 
      }
        
  }

      else if (Speed > BackSpeed) // Bilen kör framåt ochsvänger rätt
      {
       if (leftsensor<Safe)
       {
          angle = map(leftsensor, Safe, Near,  Straight, TurnRight);
          myservo.write(angle); 
       }
       else if (rightsensor<Safe)
       {
          angle = map(rightsensor, Safe, Near,  Straight, TurnLeft);
          myservo.write(angle); 
       }       
       else myservo.write(Straight);
       
  // Skriver ut sensor data:
  /*
        Serial.print("\n");
        Serial.print("left sensor= ");
        Serial.print(leftsensor);
        Serial.print("\n");
  
        Serial.print("Middle Sensor= ");
        Serial.print(middlesensor);
        Serial.print("\n");
   
        Serial.print("Right Sensor= ");
        Serial.print(rightsensor);
       Serial.print("\n");
   */
      Serial.print("Speed= ");
        Serial.print(Speed);
       Serial.print("\n");
      Serial.println();
    }
    dataReady = false;
  }
  }
 

 
 

}
