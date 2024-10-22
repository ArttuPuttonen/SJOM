// #include <Arduino.h>

// // Muuttujat
// int termistorPin = A0;        // Analoginen pinni, johon termistori on kytketty
// int numSamples = 10;          // Näytteiden lukumäärä
// float steinhartA = 0.3009249522e-03;  // Steinhart-Hart vakiot
// float steinhartB = 2.378405444e-04;
// float steinhartC = 2.019202697e-07;
// int seriesResistor = 10000;   // Jännitenjakopiirissä käytetty vastus (10kΩ)

// void setup() {
//   Serial.begin(9600);         // Aloita sarjayhteys nopeudella 9600 bps
// }

// void loop() {
//   float avgReading = 0;       // Muuttuja keskiarvolle
//   float temperature;          // Lämpötila muuttuja
//   float resistance;           // Termistorin resistanssi

//   // Ota 10 näytettä
//   for (int i = 0; i < numSamples; i++) {
//     avgReading += analogRead(termistorPin);  // Kerätään näytteet yhteen
//     delay(10);                               // Viive näytteiden välissä
//   }

//   // Laske keskiarvo
//   avgReading /= numSamples;

//   // Muunna keskiarvo vastaavaksi jännitteeksi (0-5V)
//   float voltage = avgReading * (5.0 / 1023.0);

//   // Laske termistorin resistanssi jännitenjakoyhtälön avulla
//   resistance = (5.0 / voltage - 1.0) * seriesResistor;

//   // Steinhart-Hart yhtälön avulla lasketaan lämpötila
//   float logR = log(resistance);
//   temperature = 1.0 / (steinhartA + steinhartB * logR + steinhartC * pow(logR, 3));

//   // Muunna Kelvinistä Celsiukseen
//   temperature =  (temperature - 273.15);

//   // Tulosta lämpötila sarjamonitoriin
//   Serial.print("Lämpötila: ");
//   Serial.print(temperature);
//   Serial.println(" C");

//   // Viive ennen uutta) mittausta
//   delay(1000);
// }
