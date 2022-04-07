#include <Servo.h>
#include <Wire.h>
#include <OPT3101.h>


Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int i = 0;


void setup() {
  myservo.attach(5);  // attaches the servo on pin 9 to the servo object
                      // gul till pin 9, röd till 5v och brun till ground
  Serial.begin(9600);
}

void loop() {
    Serial.print("test");
    for(int i = 0; i < 160; i++)
    {
      pos = i;
      myservo.write(pos);// 60 - 140, 60 är full höger, 140 är full vänster. runt 100 är rakt                
      delay(15);
    }
    for(int i = 160; i > 0; i--)
    {
      pos = i;
      myservo.write(pos);// 60 - 140, 60 är full höger, 140 är full vänster. runt 100 är rakt                
      delay(15);
    }    
    // tell servo to go to position in variable 'pos'
                           // waits 15ms for the servo to reach the position
  

}
