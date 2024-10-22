// #include <Arduino.h>  // Sisällytetään Arduino-kirjasto, joka tarjoaa toiminnallisuudet mikro-ohjelmointiin.

// int sensorPin = A4;    // Määritellään analogisen anturin nastaksi A4.
// int ledPin = 9;        // LEDin ohjausnasta on digitaalinasta 9.
// int sensorValue = 0;   // Muuttuja anturin arvon tallentamista varten.
// int val;               // Muuttuja, joka tallentaa ADC-lukeman väliaikaisesti.
// int ledState = LOW;    // LEDin tila (matala/korkea).

// void ADC_init();       // ADC:n alustamisen funktioprototyyppi.
// uint16_t ADC_read(uint8_t ch);  // ADC-lukufunktion funktioprototyyppi.

// void setup()
// {
//   Serial.begin(9600);      // Aloitetaan sarjayhteys nopeudella 9600 bittiä sekunnissa.
//   pinMode(ledPin, OUTPUT); // Määritellään ledPin lähtönastaksi.
//   digitalWrite(ledPin, LOW); // LED sammutetaan alussa.
//   ADC_init();              // Alustetaan ADC rekisteriasetuksilla.
// }

// void loop()
// {
//   uint16_t sensorValue = ADC_read(A4);  // Luetaan anturin arvo käyttämällä ADC_read-funktiota ja tallennetaan sensorValueen.
//   Serial.println(sensorValue);          // Tulostetaan anturin arvo sarjaliikenteeseen.
//   analogWrite(ledPin, sensorValue/4);   // Säädetään LEDin kirkkautta PWM:llä, jakamalla arvo 4:llä, koska analogWrite tukee arvoja 0-255.
//   delay(300);                           // Viive 300 millisekuntia ennen seuraavaa lukemaa.
// }   

// void ADC_init()
// {
//   // ADC-rekisterien asetukset
//   ADMUX |= (1 << REFS0) | (1 << MUX2); 
//   // ADMUX-rekisterin bitit:
//   // REFS0: Viitejännitteeksi valitaan AVcc (jännitesyöttö).
//   // MUX2: Valitaan analoginen kanava A4 (MUX2 = 1, MUX1 = 0, MUX0 = 0).

//   ADCSRA |= (1 << ADEN);  // ADEN: ADC-moduuli otetaan käyttöön (ADEN = 1).
//   ADCSRB = 0x00;          // ADCSRB nollataan, koska sitä ei tarvita tässä.
// }

// uint16_t ADC_read(uint8_t ch)
// {
//   // Aloitetaan ADC-muunnos
//   ADCSRA |= (1 << ADSC);  // ADSC: Aloita muunnos asettamalla ADSC-bitti päälle.
//   Serial.println(ADCSRA, BIN);  // Tulostetaan ADCSRA-rekisterin tila binäärimuodossa sarjaliikenteeseen.

//   // Odotetaan, kunnes muunnos on valmis (ADSC-bitti tyhjenee, kun muunnos on valmis).
//   while (ADCSRA & B01000000)
//   {
//     ;  // Tyhjä silmukka odottaa, kunnes muunnos on valmis.
//   }
  
//   Serial.println(ADCSRA, BIN);  // Tulostetaan ADCSRA uudelleen, kun muunnos on valmis.
  
//   val = ADC;  // Luetaan ADC-arvo ja tallennetaan muuttujaan 'val'.
//   return val; // Palautetaan ADC-arvo funktiosta.
// }
