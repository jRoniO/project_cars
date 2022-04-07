// Lilla motordrivaren med PWM
// Arduino UNO, TB6612FNG, potentiometer

#define PWM1 3 // PWM
#define AIN1 4 // Motor
#define AIN2 5 // Motor 

int pot;
int out;

void setup() {
  Serial.begin(9600);
  pinMode(PWM1,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  
}
 
void loop() {

  /* Motorn snurrar moturs eller medurs
   *  Ändra High/Low eller PIN för att 
   *  byta håll.
   */
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);

  pot=analogRead(A0); // Potentiometer på PORT A0
  out=map(pot,0,1023, 0, 255);
  analogWrite(PWM1,out); // Hastighetskontroll för motorn.
 
}
