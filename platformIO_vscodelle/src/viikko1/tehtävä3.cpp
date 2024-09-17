// #include <Arduino.h>

// // // C++ code
// // //
// // // Määritellään 7-segmentin segmenttien pinnit
// // const int segA = 2;
// // const int segB = 3;
// // const int segC = 4;
// // const int segD = 5;
// // const int segE = 6;
// // const int segF = 7;
// // const int segG = 8;

// // void setup() {
// //   // Määritellään kaikki segmenttien pinnit lähtöpinneiksi
// //   pinMode(segA, OUTPUT);
// //   pinMode(segB, OUTPUT);
// //   pinMode(segC, OUTPUT);
// //   pinMode(segD, OUTPUT);
// //   pinMode(segE, OUTPUT);
// //   pinMode(segF, OUTPUT);
// //   pinMode(segG, OUTPUT);
// // }

// // void kaikkiSegmentitPaalle() {
// //   digitalWrite(segA, HIGH);
// //   digitalWrite(segB, HIGH);
// //   digitalWrite(segC, HIGH);
// //   digitalWrite(segD, HIGH);
// //   digitalWrite(segE, HIGH);
// //   digitalWrite(segF, HIGH);
// //   digitalWrite(segG, HIGH);
// // }

// // void kaikkiSegmentitPois() {
// //   digitalWrite(segA, LOW);
// //   digitalWrite(segB, LOW);
// //   digitalWrite(segC, LOW);
// //   digitalWrite(segD, LOW);
// //   digitalWrite(segE, LOW);
// //   digitalWrite(segF, LOW);
// //   digitalWrite(segG, LOW);
// // }

// // void loop() {
// //   int viive = 500; // 500 millisekunnin viive

// //   // Sammutetaan kaikki segmentit alussa
// //   kaikkiSegmentitPois();

// //   // Sytytetään segmentit yksitellen
// //   digitalWrite(segA, HIGH); // Sytytä A-segmentti
// //   delay(viive);
// //   digitalWrite(segA, LOW); // Sammuta A-segmentti

// //   digitalWrite(segB, HIGH); // Sytytä B-segmentti
// //   delay(viive);
// //   digitalWrite(segB, LOW); // Sammuta B-segmentti

// //   digitalWrite(segC, HIGH); // Sytytä C-segmentti
// //   delay(viive);
// //   digitalWrite(segC, LOW); // Sammuta C-segmentti

// //   digitalWrite(segD, HIGH); // Sytytä D-segmentti
// //   delay(viive);
// //   digitalWrite(segD, LOW); // Sammuta D-segmentti

// //   digitalWrite(segE, HIGH); // Sytytä E-segmentti
// //   delay(viive);
// //   digitalWrite(segE, LOW); // Sammuta E-segmentti

// //   digitalWrite(segF, HIGH); // Sytytä F-segmentti
// //   delay(viive);
// //   digitalWrite(segF, LOW); // Sammuta F-segmentti

// //   digitalWrite(segG, HIGH); // Sytytä G-segmentti
// //   delay(viive);
// //   digitalWrite(segG, LOW); // Sammuta G-segmentti

// //   // Lopuksi sytytetään kaikki segmentit kerralla
// //   kaikkiSegmentitPaalle();
// //   delay(2000); // Pidetään kaikki päällä 2 sekuntia

// //   // Sammutetaan kaikki segmentit
// //   kaikkiSegmentitPois();
// //   delay(2000); // Odotetaan 2 sekuntia ennen seuraavaa kiertoa
// // }


// // Määritellään 7-segmentin segmenttien pinnit
// const int segA = 2;
// const int segB = 3;
// const int segC = 4;
// const int segD = 5;
// const int segE = 6;
// const int segF = 7;
// const int segG = 8;

// // Määritellään numerot 0–9 segmenttien kytkentöjen avulla
// const bool numbers[10][7] = {
//   {1, 1, 1, 1, 1, 1, 0}, // 0: A, B, C, D, E, F (G off)
//   {0, 1, 1, 0, 0, 0, 0}, // 1: B, C
//   {1, 1, 0, 1, 1, 0, 1}, // 2: A, B, D, E, G
//   {1, 1, 1, 1, 0, 0, 1}, // 3: A, B, C, D, G
//   {0, 1, 1, 0, 0, 1, 1}, // 4: B, C, F, G
//   {1, 0, 1, 1, 0, 1, 1}, // 5: A, D, E, F, G
//   {1, 0, 1, 1, 1, 1, 1}, // 6: A, C, D, E, F, G
//   {1, 1, 1, 0, 0, 0, 0}, // 7: A, B, C
//   {1, 1, 1, 1, 1, 1, 1}, // 8: A, B, C, D, E, F, G
//   {1, 1, 1, 1, 0, 1, 1}  // 9: A, B, C, D, F, G
// };

// void setup() {
//   // Määritellään segmenttien pinnit lähtöpinneiksi
//   pinMode(segA, OUTPUT);
//   pinMode(segB, OUTPUT);
//   pinMode(segC, OUTPUT);
//   pinMode(segD, OUTPUT);
//   pinMode(segE, OUTPUT);
//   pinMode(segF, OUTPUT);
//   pinMode(segG, OUTPUT);
// }

// void displayNumber(int number) {
//   // Näytetään numero segmentillä
//   bool segments[7] = {0};
  
//   if (number >= 0 && number <= 9) {
//     for (int i = 0; i < 7; i++) {
//       segments[i] = numbers[number][i];
//     }
//   }
  
//   digitalWrite(segA, segments[0]);
//   digitalWrite(segB, segments[1]);
//   digitalWrite(segC, segments[2]);
//   digitalWrite(segD, segments[3]);
//   digitalWrite(segE, segments[4]);
//   digitalWrite(segF, segments[5]);
//   digitalWrite(segG, segments[6]);
// }

// void loop() {
//   for (int i = 0; i < 10; i++) {
//     displayNumber(i);
//     delay(1000); // Näytetään numero 1 sekunnin ajan
//   }
// }
