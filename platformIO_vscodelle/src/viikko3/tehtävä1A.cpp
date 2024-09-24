#include <Arduino.h>
#include <TimerOne.h>  // TimerOne-kirjasto

// Määritellään LEDien pin numerot
const int redLED = 11;
const int yellowLED = 10;
const int greenLED = 9;

bool ledState = false;  // Muuttuja LEDien tilan seuraamiseen

void toggleLEDs() {
  // Vaihdetaan LEDien tila
  ledState = !ledState;
  
  if (ledState) {
    // Sytytetään LEDit
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, HIGH);
  } else {
    // Sammutetaan LEDit
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
  }
}

void setup() {
  // Asetetaan LED pinnit ulostuloiksi
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  
  // Asetetaan ajastin keskeyttämään joka 500 ms (0.5 sekuntia)
  Timer1.initialize(500000);  // 500000 mikrosekuntia = 500 ms
  Timer1.attachInterrupt(toggleLEDs);  // Liitetään keskeytys funktioon
}



void loop() {
  // Ei tarvita mitään koodia loop-funktiossa, koska ajastinkeskeytys hoitaa vilkutuksen
}
