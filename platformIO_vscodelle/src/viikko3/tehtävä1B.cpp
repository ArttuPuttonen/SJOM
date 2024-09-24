// #include <Arduino.h>
// #include <TimerOne.h>  // TimerOne-kirjasto

// // Määritellään LEDien pin numerot
// const int redLED = 11;    // LED 1
// const int yellowLED = 10; // LED 2
// const int greenLED = 9;   // LED 3

// // Muuttujat LEDien tilojen seuraamiseen
// bool redState = false;
// bool yellowState = false;
// bool greenState = false;

// // Laskurit keskeytyksille
// int redCounter = 0;
// int yellowCounter = 0;
// int greenCounter = 0;

// // Aikavälit LEDien vilkutukseen (500 ms yksiköissä)
// const int redInterval = 1;    // 500 ms
// const int yellowInterval = 2; // 1 sekunti
// const int greenInterval = 4;  // 2 sekuntia

// void toggleLEDs() {
//   // LED 1 (punainen) vaihtaa tilaa 500 ms välein
//   redCounter++;
//   if (redCounter >= redInterval) {
//     redState = !redState;  // Vaihda tila
//     digitalWrite(redLED, redState ? LOW : HIGH);  // LOW tarkoittaa päällä
//     redCounter = 0;  // Nollaa laskuri
//   }

//   // LED 2 (keltainen) vaihtaa tilaa 1 sekunnin välein (1000 ms)
//   yellowCounter++;
//   if (yellowCounter >= yellowInterval) {
//     yellowState = !yellowState;  // Vaihda tila
//     digitalWrite(yellowLED, yellowState ? HIGH : LOW);  // HIGH tarkoittaa päällä
//     yellowCounter = 0;  // Nollaa laskuri
//   }

  

//   // LED 3 (vihreä) vaihtaa tilaa 2 sekunnin välein (2000 ms)
//   greenCounter++;
//   if (greenCounter >= greenInterval) {
//     greenState = !greenState;  // Vaihda tila
//     digitalWrite(greenLED, greenState ? HIGH : LOW);  // HIGH tarkoittaa päällä
//     greenCounter = 0;  // Nollaa laskuri
//   }

// }

// void setup() {
//   // Asetetaan LED pinnit ulostuloiksi
//   pinMode(redLED, OUTPUT);
//   pinMode(yellowLED, OUTPUT);
//   pinMode(greenLED, OUTPUT);

//   // Asetetaan ajastin keskeyttämään joka 500 ms (0.5 sekuntia)
//   Timer1.initialize(500000);  // 500000 mikrosekuntia = 500 ms
//   Timer1.attachInterrupt(toggleLEDs);  // Liitetään keskeytys funktioon
// }


// void loop() {
//   // Ei tarvita mitään koodia loop-funktiossa, koska ajastinkeskeytys hoitaa vilkutuksen
// }
