// Test of the light sensor
// This has been tested in a bridge with a 10ko resistor
// Results : 
// Max : 1018
// Min : 309
#define PINLUMI A5

int min = 1000;
int max = 500;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(PINLUMI);
  Serial.print(sensorValue);
  Serial.print("   Min :");
  Serial.print(min);
  Serial.print("   Max :");
  Serial.println(max);
  delay(100);        // delay in between reads for stability
  if(sensorValue > max)
    max = sensorValue;
  if(sensorValue < min)
    min = sensorValue;
}


