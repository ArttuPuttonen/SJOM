// #include <Arduino.h>

// // Muuttujat
// int potentiometriPin = A0;  // A0 on analoginen sisäänmeno, johon potentiometri on kytketty
// int potentiometriArvo = 0;  // Muuttuja potentiometrin arvolle
// float jannite = 0.0;        // Muuttuja jännitteen laskemiseen

// void setup() {
//   // Aseta sisäinen viitejännite
//   analogReference(INTERNAL);

//   // Käynnistetään sarjaportti nopeudella 9600 bps
//   Serial.begin(9600);
// }

// void loop() {
//   // Lue potentiometrin arvo (AD-muunnoksen tulos 0-1023)
//   potentiometriArvo = analogRead(potentiometriPin);

//   // Muunna AD-muunnosarvo vastaavaksi jännitteeksi (1.1V sisäinen referenssi)
//   jannite = potentiometriArvo * (1.1 / 1023.0);  // Sisäinen referenssi jännite on 1.1V

//   // Tulostetaan sarjamonitoriin AD-muunnoksen arvo ja jännite
//   Serial.print("AD-muunnosarvo: ");
//   Serial.print(potentiometriArvo);
//   Serial.print("\tJännite: ");
//   Serial.println(jannite);

//   // Odotetaan 100 millisekuntia, jotta sarjamonitorin lukeminen on helpompaa
//   delay(100);
// }
