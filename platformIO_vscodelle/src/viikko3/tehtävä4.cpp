// #include <Arduino.h>

// // Määritellään LEDien pin numerot
// const int redLED = 11;    // Punainen valo
// const int yellowLED = 10; // Keltainen valo
// const int greenLED = 9;   // Vihreä valo

// // Määritellään napin pin
// const int buttonPin = 2;  // Nappi kytketty pinniin 2

// volatile bool yellowBlinking = false;  // Muuttuja keltaisen valon vilkkumiselle
// volatile bool normalSequenceActive = true;  // Muuttuja normaalin sekvenssin hallinnalle

// // Aikamuuttujat sekvenssin hallintaan
// unsigned long previousMillisYellow = 0;  // Aika keltaisen vilkkumiseen
// const long intervalYellow = 500;          // Vilkkumisväli 500 ms

// unsigned long previousMillisTraffic = 0;  // Aika liikennevalosekvenssiin
// const long greenDuration = 3000;           // Vihreän keston aika
// const long yellowDuration = 1000;          // Keltaisen keston aika
// const long redDuration = 3000;             // Punaisen keston aika
// const long redYellowDuration = 1000;       // Punainen ja keltainen yhdessä

// // Liikennevalosekvenssin tila
// enum TrafficLightState {GREEN, YELLOW, RED, RED_YELLOW};
// TrafficLightState currentState = GREEN;

// void toggleYellowBlink() {
//   yellowBlinking = !yellowBlinking;  // Vaihda keltaisen vilkkumisen tila
//   normalSequenceActive = !yellowBlinking;  // Normaalin sekvenssin tila käänteinen keltaisen vilkkumiselle
// }

// void blinkYellow() {
//   // Jos keltaisen vilkkuminen on aktiivinen
//   if (yellowBlinking) {
//     // Sammuta vihreä ja punainen valo keltaisen vilkkumisen alkaessa
//     digitalWrite(greenLED, LOW);  // Sammuta vihreä valo
//     digitalWrite(redLED, LOW);     // Sammuta punainen valo

//     unsigned long currentMillis = millis();  // Haetaan nykyinen aika

//     // Tarkistetaan, onko aika vaihtaa LEDin tilaa
//     if (currentMillis - previousMillisYellow >= intervalYellow) {
//       previousMillisYellow = currentMillis;  // Tallennetaan nykyinen aika

//       // Vilkutetaan keltaista valoa
//       static bool ledState = LOW;  // LEDin tila
//       digitalWrite(yellowLED, ledState);  // Asetetaan LEDin tila
//       ledState = !ledState;  // Vaihdetaan tilaa
//     }
//   } else {
//     digitalWrite(yellowLED, LOW);  // Sammuta keltainen valo, jos ei vilkku
//   }
// }

// void startTrafficSequence() {
//   unsigned long currentMillis = millis();  // Haetaan nykyinen aika

//   // Normaalin liikennevalosekvenssin suoritus
//   if (normalSequenceActive) {
//     switch (currentState) {
//       case GREEN:
//         digitalWrite(greenLED, HIGH);  // Sytytä vihreä valo
//         if (currentMillis - previousMillisTraffic >= greenDuration) {
//           previousMillisTraffic = currentMillis;  // Tallennetaan nykyinen aika
//           digitalWrite(greenLED, LOW);  // Sammuta vihreä valo
//           currentState = YELLOW;  // Siirry seuraavaan tilaan
//         }
//         break;

//       case YELLOW:
//         digitalWrite(yellowLED, HIGH);  // Sytytä keltainen valo
//         if (currentMillis - previousMillisTraffic >= yellowDuration) {
//           previousMillisTraffic = currentMillis;  // Tallennetaan nykyinen aika
//           digitalWrite(yellowLED, LOW);  // Sammuta keltainen valo
//           currentState = RED;  // Siirry seuraavaan tilaan
//         }
//         break;

//       case RED:
//         digitalWrite(redLED, HIGH);  // Sytytä punainen valo
//         if (currentMillis - previousMillisTraffic >= redDuration) {
//           previousMillisTraffic = currentMillis;  // Tallennetaan nykyinen aika
//           digitalWrite(redLED, LOW);  // Sammuta punainen valo
//           currentState = RED_YELLOW;  // Siirry seuraavaan tilaan
//         }
//         break;

//       case RED_YELLOW:
//         digitalWrite(redLED, HIGH);  // Sytytä punainen valo
//         digitalWrite(yellowLED, HIGH);  // Sytytä keltainen valo
//         if (currentMillis - previousMillisTraffic >= redYellowDuration) {
//           previousMillisTraffic = currentMillis;  // Tallennetaan nykyinen aika
//           digitalWrite(redLED, LOW);  // Sammuta punainen valo
//           digitalWrite(yellowLED, LOW);  // Sammuta keltainen valo
//           currentState = GREEN;  // Palataan vihreään
//         }
//         break;
//     }
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
//   digitalWrite(redLED, LOW);      // Sammuta punainen valo
//   digitalWrite(yellowLED, LOW);   // Sammuta keltainen valo
//   digitalWrite(greenLED, LOW);    // Sammuta vihreä valo
// }

// void loop() {
//   // Suoritetaan liikennevalosekvenssi ja vilkkuva keltainen valo
//   startTrafficSequence();
//   blinkYellow();
// }
