// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 
int incomingInt;
int potpin = 0;  // analog pin used to connect the potentiometer

void setup() 
{ 
  myservo.attach(8);  // attaches the servo on pin 5 to the servo object 
  Serial.begin(9600); // some servos doesn't work without Serial
} 

void loop() 
{ 
  if(Serial.available() > 0)
  {
    // read the incoming byte:
    incomingInt = Serial.parseInt();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingInt, DEC);
    if(incomingInt > 179 || incomingInt <0)
      Serial.println("Error : value received incorrect");
    else {
      Serial.print("Setting servo to : ");
      Serial.println(incomingInt, DEC);
      myservo.write(incomingInt);                  // sets the servo position according to the scaled value 
      delay(15);
    }
  }  // waits for the servo to get there 
}




