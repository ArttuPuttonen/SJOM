#include <Arduino.h>

#define RED_LED    PB3
#define YELLOW_LED PB2
#define GREEN_LED  PB1

void setup() {
    DDRB |= (1 << RED_LED) | (1 << YELLOW_LED) | (1 << GREEN_LED);

    PORTB |= (1 << GREEN_LED);
    delay(1000);
    PORTB &= ~(1 << GREEN_LED);
    
    PORTB |= (1 << YELLOW_LED);
    delay(1000);
    PORTB &= ~(1 << YELLOW_LED);
    
    PORTB |= (1 << RED_LED);
    delay(1000);
    PORTB &= ~(1 << RED_LED);
}

void loop() {
    PORTB |= (1 << GREEN_LED);
    PORTB &= ~(1 << YELLOW_LED);
    PORTB &= ~(1 << RED_LED);
    delay(3000);

    PORTB &= ~(1 << GREEN_LED);
    PORTB |= (1 << YELLOW_LED);
    delay(1000);

    PORTB &= ~(1 << YELLOW_LED);
    PORTB |= (1 << RED_LED);
    delay(3000);

    PORTB |= (1 << YELLOW_LED);
    delay(1000);

    PORTB &= ~(1 << YELLOW_LED);
}
