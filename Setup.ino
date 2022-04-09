#include "header.h"

void setup() {
pinMode(MotorEnable, OUTPUT);
pinMode(MotorPWM, OUTPUT);
pinMode(StyrServo, OUTPUT);
//pinMode(RemoteStart, OUTPUT);
//pinMode(RemoteStop, OUTPUT);
pinMode(Hastighetspuls, INPUT_PULLUP);
//pinMode(remotePin, INPUT);
Serial.begin(9600);
// Wait for the serial port to be opened before printing
// messages (only applies to boards with native USB).
while (!Serial) {}
Wire.begin();
sensor.init();
sensor.setContinuousMode();
sensor.enableDataReadyOutput(1);
sensor.setFrameTiming(32);
sensor.setChannel(OPT3101ChannelAutoSwitch);
//sensor.setChannel(0);
//sensor.setChannel(2);
sensor.setBrightness(OPT3101Brightness::Adaptive);
attachInterrupt(digitalPinToInterrupt(SensorInterrupt), setDataReadyFlag, RISING);
sensor.enableTimingGenerator();
Wire.begin();
Wire.beginTransmission(0x68); // Begins a transmission to the I2C slave (GY-521board)
Wire.write(0x6B); // PWR_MGMT_1 register
Wire.write(0); // set to zero (wakes up the MPU-6050)
Wire.endTransmission(true);

//Servo
myservo.attach(StyrServo);
myservo.write(90);
delay(1000);


//PID
//Vänster PID
LeftPID.SetMode(AUTOMATIC);
LeftPID.SetOutputLimits(0,127);
LeftPID.SetSampleTime(1);

//Höger PID
RightPID.SetMode(AUTOMATIC);
RightPID.SetOutputLimits(0,127);
RightPID.SetSampleTime(1);

//Speed PID
SpeedPID.SetMode(AUTOMATIC);
SpeedPID.SetOutputLimits(30,250);
SpeedPID.SetSampleTime(500);

//Grundinställningar på utgångar
digitalWrite(MotorEnable,1);
analogWrite(MotorPWM,20);

}
