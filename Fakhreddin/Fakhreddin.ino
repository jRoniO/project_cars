#include "header.h"


void setup() 
{
  myservo.attach(servoPin); //sätter igång sensor
   myservo.write(90); // sätter sensor till 90
   Wire.begin();
   Serial.begin(9600); // sätter igång serial överföring.

  
  while (!Serial) {}

  sensor.init();
  if (sensor.getLastError()) // om något fel med sensor skriv Failed to initialize OPT3101: error
  {
    Serial.print(F("Failed to initialize OPT3101: error "));
    Serial.println(sensor.getLastError());
    while (1) {}
  }
  // aktiverar sensors olika funktioner genom sensors biblotek.
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
leftsensor = distances[0];  // Döper om vänster sensor från distances[0] till leftsensor
middlesensor = distances[1];  // Döper om vänster sensor från distances[1] till middlesensor
rightsensor = distances[2];  // Döper om vänster sensor från distances[2] till rightsensor


  
 if (dataReady) // om sensor är på gång
  {
    sensor.readOutputRegs();
    distances[sensor.channelUsed] = sensor.distanceMillimeters;
      
      
  
   if (sensor.channelUsed == 2)
    {
      if (leftsensor<Safe && rightsensor> leftsensor) // if för höger sväng
       {
          angle = map(leftsensor, Safe, Near,  Straight, TurnRight); // map funktion för smidigare sväng
          myservo.write(angle); 
          
       }
    
      else if (rightsensor<Safe && rightsensor<leftsensor)  // if för vänster sväng
       {
          angle = map(rightsensor, Safe, Near,  Straight, TurnLeft);// map funktion för smidigare sväng
          myservo.write(angle); 
         
       }      

           else if (middlesensor<NotSafe && rightsensor<leftsensor)  // if för höger sväng men om väggen framför närmar sig
       {
          angle = map(rightsensor, Safe, Near,  Straight, TurnRight);// map funktion för smidigare sväng
          myservo.write(angle); 
         
       }      

           else if (middlesensor<NotSafe && rightsensor>leftsensor) // if för vänster sväng men om väggen framför närmar sig
       {
          angle = map(rightsensor, Safe, Near,  Straight, TurnLeft);// map funktion för smidigare sväng
          myservo.write(angle); 
         
       }      
        
       else myservo.write(Straight); // bilen kör framåt


    
       
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
 

 
 
