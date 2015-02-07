/*
Temp monitor displayed on LCD screen and sent to serial
 Author : Julien Vallini
 */

// include the library code:
#include <LiquidCrystal.h>
#include <DHT.h>
#include <Time.h>
#include <TimeAlarms.h>
#include <Servo.h> 

#define DHTTYPE DHT22
#define DHTPIN 7
#define DATAPIN 13
#define LUMIPIN A5
#define SERVOPIN 8

DHT dht(DHTPIN, DHTTYPE);
float h;
float t;
float f;
float hi;
float lumi;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int lcdSquare;
int incomingInt=90;
Servo myservo;

// Parameters
//void (*serial_mode)() = serialTextLoop; // Function to call to send data to the serial
void (*serial_mode)() = serialJsonLoop; // Function to call to send data to the serial
float sensorTempo = 2; // Delay between two calls of the sensor


void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600); 
  Alarm.timerRepeat(sensorTempo, sensorLoop);
  sensorLoop(); // One execution of the sensorLoop to initiate the variables
  dht.begin();
  lcd.clear();
  pinMode(DATAPIN, OUTPUT); 
  myservo.attach(SERVOPIN);  // attaches the servo on pin 5 to the servo object 
  myservo.write(incomingInt);


}

void loop() {
  lcdLoop();
  serialReadLoop();
  Alarm.delay(150);
}

void serialReadLoop() {
  if(Serial.available() > 0)
  {
    // read the incoming byte:
    incomingInt = Serial.parseInt();

    String servStatus;

    // say what you got:
    Serial.println(incomingInt, DEC);
    if(incomingInt > 180 || incomingInt < 1 ) // Value should be comprised between 1 and 180
      servStatus = "ERR";
    else {
      myservo.write(incomingInt);                  // sets the servo position according to the scaled value 
      servStatus = "OK";
      delay(15);
    }

    Serial.print("{\"s\":\"");
    Serial.print(servStatus);
    Serial.print(	"\", \"v\":\"");
    Serial.print(incomingInt);
    Serial.println(	"\"}");

  }  // waits for the servo to get there 
}

void lcdLoop() {

  lcd.setCursor(0, 0);
  lcd.print("T:"); 
  lcd.print(t);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(9, 0);
  lcd.print("L:");
  lcd.print(lumi);
  lcd.setCursor(9, 1);
  lcd.print("S:");
  lcd.print(incomingInt);
}
void sensorLoop() {
  digitalWrite(DATAPIN, HIGH);
  h = dht.readHumidity();
  t = dht.readTemperature();
  f = dht.readTemperature(true);
  hi = dht.computeHeatIndex(f, h);
  lumi = analogRead(LUMIPIN);
  (*serial_mode)();
  digitalWrite(DATAPIN, LOW); 

  // Cleans the lcd values
  lcd.setCursor(2, 0);
  lcd.print("     ");
  lcd.setCursor(2, 1);
  lcd.print("     ");
  lcd.setCursor(11, 0);
  lcd.print("     ");
  lcd.setCursor(11, 1);
  lcd.print("     ");

}

// Sends datas as json to serial
void serialJsonLoop() {
  Serial.print("{\"h\":\"");
  Serial.print(h);
  Serial.print(	"\", \"t\":\"");
  Serial.print(t);
  Serial.print(	"\", \"f\":\"" );
  Serial.print(f);
  Serial.print(	"\", \"hi\":\"" );
  Serial.print(hi);
  Serial.print(	"\", \"lumi\":\"" );
  Serial.print(lumi);
  Serial.println(	"\"}");

}

// Sends datas as text to serial
void serialTextLoop() {
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // Compute heat index
  // Must send in temp in Fahrenheit!
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.print(" *F\t");
  Serial.print("Luminance: ");
  Serial.print(lumi);
}















