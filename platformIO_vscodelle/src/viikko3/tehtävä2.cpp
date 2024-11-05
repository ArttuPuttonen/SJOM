// #include <Arduino.h>
// // Määritellään napin ja LEDin pinnit
// const int buttonPin = 2;  // Nappi kytketty pinniin 2
// const int ledPin = 13;    // Sisäänrakennettu LED kytketty pinniin 13

// volatile int interruptCounter = 0;  // Laskuri keskeytyksille


// void toggleLED() {
//   // Vaihdetaan LEDin tila
//   digitalWrite(ledPin, !digitalRead(ledPin));
//   // Kasvatetaan keskeytyslaskuria
//   interruptCounter++;
// }


// void setup() {
//   // Asetetaan LED ulostuloksi
//   pinMode(ledPin, OUTPUT);
//   // Asetetaan nappi sisääntuloksi
//   pinMode(buttonPin, INPUT_PULLUP);

//   // Liitetään keskeytys napin painallukseen (FALLING-moodi)
//   attachInterrupt(digitalPinToInterrupt(buttonPin), toggleLED, FALLING);

//   // Sarjamonitorin käynnistys
//   Serial.begin(9600);
// }

// void loop() {
//   // Tulostetaan keskeytysten määrä sarjamonitoriin
//   Serial.print("Keskeytysten määrä: ");
//   Serial.println(interruptCounter);
//   delay(1000);  // Päivitetään joka sekunti
// }
