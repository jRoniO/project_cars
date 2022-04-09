
#include "header.h"

void setDataReadyFlag()
{
  dataReady = true;
}

void loop() 
{
//remoteVal = digitalRead(remotePin);
//if (remoteVal == 1)
{

  if((LastSpeedCheck< millis()-500))
{
LastSpeedCheck=millis();
Speed=puls;
puls=0;
}
if (digitalRead(Hastighetspuls)!=pulsStatus)
{
pulsStatus=digitalRead(Hastighetspuls);
if (digitalRead(Hastighetspuls))
{
puls++;
}




}

if (dataReady)
{
sensor.readOutputRegs();
distances[sensor.channelUsed] = sensor.distanceMillimeters;
dataReady = false;
}

LeftSensor = (distances[2]);
RightSensor = (distances[0]);
MiddleSensor = (distances[1]);

SetPoint=(RightSensor+LeftSensor)*1;

LeftInput=LeftSensor;
RightInput=RightSensor;
RightPID.Compute();
LeftPID.Compute();
SpeedPID.Compute();

//Servo

  pid.read_sensors(LeftInput, RightInput); 
  pid.regulate();
  myservo.write(pid.output);
  Serial.print("Output angle: ");
  Serial.println(pid.output);
  //delay(1000);

/*
 if((LeftOutput<30)&&(RightOutput>-60))
          Output=(100);
        else if (LeftOutput<RightOutput)
        // variabel + 0 = min värde analogt, 1023 = max värde analogt. 255 motsvarar maxvärde digital konverterat, 0 = minvärde digitalt konverterat. 
          Output=(map(RightOutput, 0, 1023 , -127, 90 ));
        else if(LeftOutput>RightOutput)
        // variabel + 0 = min värde analogt, 1023 = max värde analogt. 255 motsvarar maxvärde digital konverterat, 0 = minvärde digitalt konverterat. 
          Output=(map(LeftOutput, 0, 1023, 127, 35));
        else
          Output=(100);

*/
analogWrite(MotorPWM,SpeedOutput);
// myservo.write(Output);
}
//else { analogWrite(MotorPWM, LOW);}
}
