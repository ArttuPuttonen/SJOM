// #include <Arduino.h>

// void setup() {
//     Serial.begin(9600);     // Alustetaan sarjaliikenne
// }

// void loop() {
//     if (Serial.available() >= 4) {          // Varmistetaan, että datta on tarpeeksi
//         char receivedData[5];               // Taulukko vastaanotettavalle viestille 
//         Serial.readBytes(receivedData, 4);  // luetaan 4 merkkiä
//         receivedData[4] = '\0';             // Lisätään lopetusmerkki merkkijonoon
//         Serial.print("Vastaanotettu: ");    
//         Serial.println(receivedData);       // Tulostetaan vastaanotettu viesti
//     }
// }