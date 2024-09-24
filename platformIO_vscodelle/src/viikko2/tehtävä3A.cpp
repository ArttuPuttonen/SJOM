#include <Arduino.h>

void printBinary(byte value) {
  for (int i = 7; i >= 0; i--) {
    Serial.print(bitRead(value, i));
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  
  byte luku1 = 170;
  byte luku2 = 204;

  byte tulos_or = luku1 | luku2;
  byte tulos_and = luku1 & luku2;
  byte tulos_xor = luku1 ^ luku2;
  byte tulos_not1 = ~luku1;
  byte tulos_not2 = ~luku2;

  Serial.println("Binaarimuodossa:");
  
  Serial.print("luku1: ");
  printBinary(luku1);
  
  Serial.print("luku2: ");
  printBinary(luku2);
  
  Serial.print("luku1 OR luku2: ");
  printBinary(tulos_or);
  
  Serial.print("luku1 AND luku2: ");
  printBinary(tulos_and);
  
  Serial.print("luku1 XOR luku2: ");
  printBinary(tulos_xor);
  
  Serial.print("NOT luku1: ");
  printBinary(tulos_not1);
  
  Serial.print("NOT luku2: ");
  printBinary(tulos_not2);
}

void loop() {}
