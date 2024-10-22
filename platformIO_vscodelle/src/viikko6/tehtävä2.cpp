// #include <Arduino.h>


// /*
//  * Pollaamalla Timer/Counter1-ylivuoto
//  * Muokattu käyttämään Timer/Counter1:aa
//  */

// const int ledPin = 13;  // LED on Arduino:n sisäinen pinni 13
// byte ledState = HIGH;   // Muuttuja LEDin tilalle (HIGH = päällä)
// int count = 0;          // Laskuri ylivuotojen laskemiseen

// void setup()
// {
//   pinMode(ledPin, OUTPUT);  // Asetetaan LED-pinni ulostuloksi

//   // Timer/Counter1:n asetukset
//   TCNT1 = 0x0000;           // Alustetaan laskuriarvo (TCNT1) nollaksi
//   TCCR1A = 0x00;            // Asetetaan Timer/Counter1 normaalitilaan (ei PWM)
  
//   // Asetetaan Timer/Counter1 esijakajaksi 1024 (määrittää kuinka nopeasti laskuri laskee)
//   TCCR1B |= (1 << CS12) | (1 << CS10); 
  
//   TIFR1 |= (1 << TOV1);     // Nollataan ylivuotolippu asettamalla se
// }

// void loop()
// {
//   // Tarkistetaan, onko Timer/Counter1 ylivuotanut (TOV1-lippu asetettu)
//   if (TIFR1 & (1 << TOV1))  // Tarkistetaan TOV1-bitti rekisteristä TIFR1
//   {
//     count++;  // Kasvatetaan ylivuotolaskuria
//     TIFR1 = (1 << TOV1);  // Nollataan ylivuotolippu kirjoittamalla siihen 1
//   }

//   // Kun ylivuotoja on tapahtunut 50
//   if (count == 50)
//   {
//     ledState = !ledState;  // Vaihdetaan LEDin tilaa (päällä/pois)
//     digitalWrite(ledPin, ledState);  // Asetetaan uusi tila LEDille
//     count = 0;  // Nollataan laskuri
//   }
// }
