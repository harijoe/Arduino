#include <LiquidCrystal.h>

int* myArray = intToArray(15486);
void setup(){
  Serial.begin(9600); 
}


void loop() {

Serial.println(myArray[0]);
Serial.println(myArray[1]);
Serial.println(myArray[2]);
Serial.println(myArray[3]);
Serial.println(myArray[4]);
Serial.println(myArray[5]);
delay(5000);
}

int* intToArray(int integer) {
  int* myArray = 0;
  myArray = (int*) malloc(sizeof(integer) * sizeof(int));
  int i=0;
do {
    myArray[i] = integer%10;
    integer = integer/10;
  }  while(integer!=0);
  return myArray;
}
