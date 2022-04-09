#ifndef HEADER_H_
#define HEADER_H_
#include <Wire.h>
#include <PID_v2.h>
#include <Servo.h>
#include <OPT3101.h>

#define SensorInterrupt 2
#define MotorEnable 4

#define MotorPWM 3
#define StyrServo 5
#define Hastighetspuls 7
//#define RemoteStart 11
//#define RemoteStop 12

struct PID_controller
{
  double target = 90;
  double output = 0x00;
  double last_error = 0x00;
  double Kp = 0x00;
  double Ki = 0x00;
  double Kd = 0x00;
  double integral = 0x00;
  double derivative = 0x00;
  double min_ = 0;
  double max_angle = 180;

  PID_controller(void) { }
  
  PID_controller(const double Kp, const double Ki, const double Kd)
  {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    return;
  }

  void read_sensors(const double left_input, const double right_input)
  {
    double LeftInput = 100;
    double RightInput = 100;
    LeftInput=(map(left_input, 0, 6000 , 0, 90 ));
    RightInput=(map(right_input, 250, -250,30, 0));
    
    this->output = this->target + LeftInput - RightInput; // skillnaden mellan vänster höger relativt till 90 grader.
    //this->output=(map(this->output, 0, 180, 100 , 0)); // Sensor, servo mappning.
    // Utskrivt mätfel.
    /*Serial.print("left: ");
    Serial.println(LeftInput);
    Serial.print("right: ");
    Serial.println(RightInput);
     delay(1000);
     */
    return;
  }

  void regulate(void)
  {
    const double error = this->target - this->output;
    Serial.print("Error: ");
    Serial.println(error);
    Serial.print("Output: ");
    Serial.println(output);
    this->integral += error;
    this->derivative = error - this->last_error;
    this->output = this->target + Kp * error + Ki * this->integral + Kd * this->derivative; // Någonting ej okej här.
    this->last_error = error;
    return;
  }
  
};

//int remotePin = 12;
//int remoteVal = 0;
double Kp=0.35, Ki=0.0, Kd=0, LeftSensor,RightSensor,MiddleSensor;
double SetPoint = 10.0, Input, Output,TotalTurnAngle;
double Speed_p=8, Speed_i=5, Speed_d=2,SpeedSetPoint = 5, SpeedOutput;
double puls=0;
bool pulsStatus=false;
//int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables foraccelerometer raw data
//int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
//int16_t temperature; // variables for temperature data
//int16_t Counter=0;
//int16_t TurboCounter=0;
unsigned long LastSpeedCheck;
int16_t SpeedTemp;
double Speed;
double LeftSetPoint=10.0, LeftInput=0,LeftOutput=0;
double RightSetPoint=0,RightInput=0,RightOutput=0;
PID LeftPID(&LeftInput,&LeftOutput,&SetPoint,Kp,Ki,Kd,DIRECT);
PID RightPID(&RightInput,&RightOutput,&SetPoint,Kp,Ki,Kd,DIRECT);
PID SpeedPID(&Speed,&SpeedOutput,&SpeedSetPoint,Speed_p,Speed_i,Speed_d,DIRECT);
OPT3101 sensor;
int16_t distances[3];
Servo myservo; // create ser

volatile bool dataReady = false;
PID_controller pid(1.35, 0.00005, 0.01); // Testa olika värden (PID). // PID_controller pid(1.35, 0.00005, 1);
// KP proportional KI = Integral KD = Derivative

#endif /* HEADER_H_ */
