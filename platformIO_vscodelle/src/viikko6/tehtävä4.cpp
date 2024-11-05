// #include <Arduino.h>
// #include <avr/wdt.h>

// const int ledPin = 9; // LED-pinni
// const int watchdogTimeout = 4; // Watchdog timeout (4 sekuntia)

// void setup() {
//   Serial.begin(9600); // Aloitetaan sarjayhteys
//   Serial.println("Ollaan setupissa"); // Tulostetaan viesti

//   pinMode(ledPin, OUTPUT); // Asetetaan LED-pinni ulostuloksi
//   wdt_enable(WDTO_4S); // Otetaan watchdog käyttöön 4 sekunnin aikarajalla
// }

// void loop() {
//   for (int i = 0; i < 5; i++) { // 5 kierrosta
//     digitalWrite(ledPin, HIGH); // Sytytetään LED
//     delay(1000); // Odotetaan 1000 ms
//     wdt_reset(); // Nollataan watchdog timer

//     digitalWrite(ledPin, LOW); // Sammutetaan LED
//     delay(1000); // Odotetaan 1000 ms
//     wdt_reset(); // Nollataan watchdog timer
//   }

//   // Voidaan lisätä muita toimintoja tai logiikkaa tässä
// }
