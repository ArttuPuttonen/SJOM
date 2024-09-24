// #include <Arduino.h>

// void setup() {
//   // Tapauksessa 1: Kaikki B-portin bitit 1:ksi
//   DDRB = 0b00111111;

//   Serial.begin(9600);
// }

// void loop() {
//   // Tapauksessa 1: Kaikki B-portin bitit 1:ksi
//   PORTB = 0b00111111;
//   Serial.println("Kaikki bitit ykkoseksi: ");
//   delay(1000);

//   PORTB = 0;
//   Serial.println("Kaikki bitit nolliksi");
//   delay(1000);
  
//   PORTB = 1 << 4;
//   Serial.println("Bitti 4 ylös: ");
//   delay(1000);

//   PORTB |= 1 << 4;
//   Serial.println("OR operaatiolla bitti 4 ylös uudelleen");
//   delay(1000);

//   // Tapaus 2: Asetetaan kaikki bitit 0:ksi
//   PORTB = 0;
//   Serial.println("Bitit nollaksi");
//   delay(1000);

//   PORTB |= (1 << 5);
//   Serial.println("Bitti 5 ylös");
//   delay(500);

//   PORTB |= (1 << 3);
//   Serial.println("Bitti 3 ylös");
//   delay(500);

//   PORTB |= (1 << 2);
//   Serial.println("Bitti 2 ylös");
//   delay(500);

//   PORTB |= (1 << 0);
//   Serial.println("Bitti 0 ylös");
//   delay(500);

//   PORTB = 0; 
//   Serial.println("Kaikki ledit pois paalta");
//   delay(1000);
// }
