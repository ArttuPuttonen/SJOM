// #include <Arduino.h>

// const int ledPin = 13;   // LED on Arduino:n sisäinen pinni 13
// byte ledState = HIGH;    // Muuttuja LEDin tilalle (HIGH = päällä)
// int count = 0;           // Laskuri ylivuotojen laskemiseen

// void setup()
// {
//   pinMode(ledPin, OUTPUT);   // Asetetaan LED-pinni ulostuloksi

//   // Timer/Counter2:n asetukset
//   TCNT2 = 0x00;              // Alustetaan laskuriarvo (TCNT2) nollaksi
//   TCCR2A = 0x00;             // Asetetaan Timer/Counter2 normaalitilaan (ei PWM)

//   // Asetetaan Timer/Counter2 esijakajaksi 1024 (määrittää kuinka nopeasti laskuri laskee)
//   TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);

//   // Keskeytyksen asetus
//   TIMSK2 |= (1 << TOIE2);    // Asetetaan keskeytys ylivuodolle (TOIE2)

//   // Nollataan keskeytyslippu varmuuden vuoksi
//   TIFR2 |= (1 << TOV2);     

//   // Aktivoidaan keskeytykset
//   sei();                     // Globaalit keskeytykset päälle
// }

// void loop()
// {
//   // loop()-funktiossa ei tarvitse tehdä mitään keskeytyksen käsittelyssä
// }

// // Timer/Counter2:n ylivuotokeskeytyksen käsittelijä
// ISR(TIMER2_OVF_vect) 
// {
//   count++;  // Kasvatetaan ylivuotolaskuria

//   // Kun ylivuotoja on tapahtunut 50
//   if (count == 50)
//   {
//     ledState = !ledState;    // Vaihdetaan LEDin tilaa (päällä/pois)
//     digitalWrite(ledPin, ledState);  // Asetetaan uusi tila LEDille
//     count = 0;  // Nollataan laskuri
//   }
// }
