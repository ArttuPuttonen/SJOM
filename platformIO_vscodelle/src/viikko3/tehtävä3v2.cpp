// #include <Arduino.h>

// // Määritellään LEDien pin numerot
// const int redLED = 11;    // Punainen valo
// const int yellowLED = 10; // Keltainen valo
// const int greenLED = 9;   // Vihreä valo

// // Määritellään napin pin
// const int buttonPin = 2;  // Nappi kytketty pinniin 2

// volatile bool yellowBlinking = false;  // Muuttuja keltaisen valon vilkkumiselle
// volatile bool normalSequenceActive = true;  // Muuttuja normaalin sekvenssin hallinnalle

// void toggleYellowBlink() {
//   yellowBlinking = !yellowBlinking;  // Vaihda keltaisen vilkkumisen tila
//   normalSequenceActive = !yellowBlinking;  // Normaalin sekvenssin tila käänteinen keltaisen vilkkumiselle
// }

// void blinkYellow() {
//   // Jos keltaisen vilkkuminen on aktiivinen, vilkuta keltainen valo
//   if (yellowBlinking) {
//     digitalWrite(yellowLED, LOW);   // Sytytä keltainen valo (LOW)
//     delay(500);                      // Odota 500 ms
//     digitalWrite(yellowLED, HIGH);  // Sammuta keltainen valo (HIGH)
//     delay(500);                      // Odota 500 ms
//   }
// }

// void startTrafficSequence() {
//   // Normaalin liikennevalosekvenssin suoritus
//   if (normalSequenceActive) {
//     // Vihreä valo palaa 3 sekuntia
//     digitalWrite(greenLED, HIGH);  // Sytytä vihreä valo (HIGH)
//     delay(3000);
//     digitalWrite(greenLED, LOW);   // Sammuta vihreä valo (LOW)

//     // Keltainen valo palaa sekunnin
//     digitalWrite(yellowLED, HIGH);  // Sytytä keltainen valo (HIGH)
//     delay(1000);
//     digitalWrite(yellowLED, LOW);   // Sammuta keltainen valo (LOW)

//     // Punainen valo palaa 3 sekuntia
//     digitalWrite(redLED, HIGH);     // Sytytä punainen valo (HIGH)
//     delay(3000);
//     digitalWrite(redLED, LOW);      // Sammuta punainen valo (LOW)

//     // Punainen ja keltainen yhdessä sekunnin ajan
//     digitalWrite(redLED, HIGH);     // Sytytä punainen valo (HIGH)
//     digitalWrite(yellowLED, HIGH);  // Sytytä keltainen valo (HIGH)
//     delay(1000);
//     digitalWrite(redLED, LOW);      // Sammuta punainen valo (LOW)
//     digitalWrite(yellowLED, LOW);   // Sammuta keltainen valo (LOW)
//   }
// }

// void setup() {
//   // Asetetaan LED pinnit ulostuloiksi
//   pinMode(redLED, OUTPUT);
//   pinMode(yellowLED, OUTPUT);
//   pinMode(greenLED, OUTPUT);

//   // Asetetaan nappi sisääntuloksi
//   pinMode(buttonPin, INPUT_PULLUP);

//   // Asetetaan keskeytys napin painallukseen (FALLING-moodi)
//   attachInterrupt(digitalPinToInterrupt(buttonPin), toggleYellowBlink, FALLING);

//   // Sarjamonitorin käynnistys (valinnainen)
//   Serial.begin(9600);

//   // Aluksi sammutetaan kaikki valot
//   digitalWrite(redLED, LOW);      // Sammuta punainen valo (LOW)
//   digitalWrite(yellowLED, LOW);   // Sammuta keltainen valo (LOW)
//   digitalWrite(greenLED, LOW);    // Sammuta vihreä valo (LOW)
// }

// void loop() {
//   // Suoritetaan liikennevalosekvenssi ja vilkkuva keltainen valo
//   startTrafficSequence();
//   blinkYellow();
// }
