#include <Arduino.h>
// Sarjatulostin - Serial Plotter esimerkki (muokattu T1)

void setup() {
  Serial.begin(115200); // Nopea sarjayhteys
  delay(10);
}

void loop() {
  int antennaSignal = analogRead(A0);       // A0-signaali
  int ramp = millis() % 100;                // Ramppi, joka nollautuu 100 ms välein

  Serial.print("A0:");                      // Tulostetaan A0-signaalin otsikko
  Serial.print(antennaSignal);              // Tulostetaan A0-signaali
  Serial.print(",");                        // Erotin
  Serial.print("Ramp:");                    // Tulostetaan ramppimuuttujan otsikko
  Serial.println(ramp);                     // Tulostetaan ramppimuuttuja

  delay(2);                                 // 2 ms välein
}
