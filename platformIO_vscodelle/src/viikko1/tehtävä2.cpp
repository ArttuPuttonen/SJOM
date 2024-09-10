#include <Arduino.h>

// Määritellään LEDien pin numerot
const int redLED = 11;
const int yellowLED = 10;
const int greenLED = 9;

// Taajuus 2 Hz tarkoittaa vilkkumisjaksoa 0.5 sekuntia (500 ms)
const int blinkInterval = 500;

void setup() {
  // Asetetaan LED pinnit ulostuloiksi
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

// Funktio LEDien sytyttämiseen ja sammuttamiseen
void turnOnRed() {
  digitalWrite(redLED, LOW);
}

void turnOffRed() {
  digitalWrite(redLED, HIGH);
}

void turnOnYellow() {
  digitalWrite(yellowLED, HIGH);
}

void turnOffYellow() {
  digitalWrite(yellowLED, LOW);
}

void turnOnGreen() {
  digitalWrite(greenLED, HIGH);
}

void turnOffGreen() {
  digitalWrite(greenLED, LOW);
}

void loop() {
  // Sytytetään kaikki kolme LEDiä
  turnOnRed();
  turnOnYellow();
  turnOnGreen();
  delay(blinkInterval);  // Odotetaan 500 ms
  
  // Sammutetaan kaikki kolme LEDiä
  turnOffRed();
  turnOffYellow();
  turnOffGreen();
  delay(blinkInterval);  // Odotetaan 500 ms
}
