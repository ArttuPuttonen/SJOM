// #include <Arduino.h>


// /* 
//  * Pollaamalla Timer/Counter0-ylivuoto
//  */

// // Määritetään LED-pin, joka on Arduino-alustassa yleensä numero 13.
// const int ledPin = 13;
// // Muuttuja LEDin tilan seuraamiseksi, aluksi HIGH (LED päällä).
// byte ledState = HIGH;
// // Laskuri, joka seuraa ajastimen ylivuotojen määrää.
// int count = 0;

// void setup()
// {
//   // Asetetaan LED-pinni ulostulotilaan.
//   pinMode(ledPin, OUTPUT);

//   // Nollataan Timer/Counter0:n laskuri.
//   TCNT0 = 0x00;           
  
//   // Asetetaan ajastimen toimintatilaksi normaali tila (ei erityisiä aaltomuotoja).
//   TCCR0A = 0x00;

//   // Asetetaan Timer/Counter0:n prescaler-arvoksi 1024.
//   // Tämä hidastaa ajastimen laskentanopeutta ja tekee ylivuototapahtumista harvinaisempia.
//   TCCR0B |= (1 << CS02) | (1 << CS00); 

//   // Nollataan ajastimen ylivuotolippu (TOV0), jotta seuraavat ylivuodot voidaan havaita.
//   TIFR0 |= (1 << TOV0);
// }

// void loop()
// {
//   // Tarkistetaan, onko ajastimen ylivuotolippu asetettu (eli onko ylivuoto tapahtunut).
//   if ((TIFR0 & (1 << TOV0)) != 0)
//   {
//     // Jos ylivuoto on tapahtunut, kasvatetaan laskuria yhdellä.
//     count++;
//     // Nollataan ylivuotolippu asettamalla TOV0-bitti, jotta voimme havaita seuraavat ylivuodot.
//     TIFR0 = (1 << TOV0);
//   }

//   // Tarkistetaan, onko laskuri saavuttanut arvon 50.
//   // Tämä tarkoittaa, että 50 ylivuotoa on tapahtunut.
//   if (count == 50)
//   {
//     // Vaihdetaan LEDin tila (sytytetään tai sammutetaan LED).
//     ledState = !ledState;
//     // Päivitetään LEDin tila fyysisesti laitteeseen.
//     digitalWrite(ledPin, ledState);
//     // Nollataan laskuri, jotta seuraavat 50 ylivuotoa voidaan laskea.
//     count = 0;
//   }
// }
