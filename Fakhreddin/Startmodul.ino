#define remotePin 12
#define RemoteStart 11

#define ENABLE_PIN 5
      
int In1 = 7;     //motor A
int In2 = 8;
int SPEED = 255;

int remoteVal = 0;


 void setup()
 {
   pinMode(RemoteStart, OUTPUT);
   pinMode(remotePin, INPUT);
 
   pinMode(In1, OUTPUT); 
   pinMode(In2, OUTPUT); 
   pinMode(ENABLE_PIN, OUTPUT);

   
   digitalWrite(In1, LOW);
   digitalWrite(In2, HIGH);

   return;
}

void loop()
{
   remoteVal = digitalRead(remotePin); // Läser av insignalen från startmodulen.
   
   if (remoteVal) 
      analogWrite(ENABLE_PIN, 255); // Motor körs i högt hastighet.
   else
      analogWrite(ENABLE_PIN, 0); // anras är motorn av.
   return; 
 }

             
