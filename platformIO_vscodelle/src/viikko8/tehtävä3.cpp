#include <Arduino.h>

void setup() {
    Serial.begin(9600);     // Alustetaan sarjaliikenne
}

void loop() {
    const char message[] = "SJOM";  // Lähetettävä viesti
    Serial.write(message);  
    delay(1000);
}