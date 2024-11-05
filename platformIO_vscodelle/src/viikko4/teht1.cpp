// #include <Arduino.h>

// // Muuttujat
// int potentiometriPin = A0;  // A0 on analoginen sisäänmeno, johon potentiometri on kytketty
// int potentiometriArvo = 0;  // Muuttuja potentiometrin arvolle
// float jannite = 0.0;        // Muuttuja jännitteen laskemiseen

// void setup() {
//   // Käynnistetään sarjaportti nopeudella 9600 bps
//   Serial.begin(9600);
// }

// void loop() {
//   // Lue potentiometrin arvo (AD-muunnoksen tulos 0-1023)
//   potentiometriArvo = analogRead(potentiometriPin);

//   // Muunna AD-muunnosarvo vastaavaksi jännitteeksi (0-5V)
//   jannite = potentiometriArvo * (5.0 / 1023.0);

//   // Tulostetaan sarjamonitoriin AD-muunnoksen arvo ja jännite
//   Serial.print("AD-muunnosarvo: ");
//   Serial.print(potentiometriArvo);
//   Serial.print("\tJännite: ");
//   Serial.println(jannite);

//   // Odotetaan 100 millisekuntia, jotta sarjamonitorin lukeminen on helpompaa
//   delay(100);
// }
