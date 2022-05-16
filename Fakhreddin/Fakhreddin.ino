#include "header.h"


void setup() 
{
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


  
 if (dataReady)
  {
    sensor.readOutputRegs();
    distances[sensor.channelUsed] = sensor.distanceMillimeters;
      
      
  
   if (sensor.channelUsed == 2)
    {
      if (leftsensor<Safe && rightsensor> leftsensor)
       {
          angle = map(leftsensor, Safe, Near,  Straight, TurnRight);
          myservo.write(angle); 
          
       }
    
      else if (rightsensor<Safe && rightsensor<leftsensor)
       {
          angle = map(rightsensor, Safe, Near,  Straight, TurnLeft);
          myservo.write(angle); 
         
       }      

           else if (middlesensor<NotSafe && rightsensor<leftsensor)
       {
          angle = map(rightsensor, Safe, Near,  Straight, TurnRight);
          myservo.write(angle); 
         
       }      

           else if (middlesensor<NotSafe && rightsensor>leftsensor)
       {
          angle = map(rightsensor, Safe, Near,  Straight, TurnLeft);
          myservo.write(angle); 
         
       }      
        
       else myservo.write(Straight);


    
       
  }
  
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
   Serial.print("Angle= ");
        Serial.print(angle);
       Serial.print("\n");
       Serial.println();
  */
    dataReady = false;
  
  }
}
 

 
 
