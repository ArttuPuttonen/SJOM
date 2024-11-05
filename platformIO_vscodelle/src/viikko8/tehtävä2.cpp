#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TCS34725.h>
#include <DFRobot_RGBLCD1602.h>
#include <SPI.h>

// Määritä I2C-osoite ja näytön koko
DFRobot_RGBLCD1602 lcd(0x27, 16, 2); // Muuta osoite tarvittaessa

// Määritä TCS34725-anturi
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
    Serial.begin(9600);
    lcd.init();  // Alustaa LCD-näytön
    lcd.setRGB(0, 255, 0); // Aseta taustavalo vihreäksi
    lcd.clear();       // Tyhjentää näytön

    if (!tcs.begin()) {
        lcd.print("Anturi ei löydy");
        while (1); // Pysäytä ohjelma, jos anturia ei löydy
    }
}

void loop() {
    uint16_t r, g, b, c;
    tcs.getRawData(&r, &g, &b, &c); // Hae raakadatan väriarvot

    // Näytetään väriarvot LCD-näytöllä
    lcd.clear();
    lcd.print("R:");
    lcd.print(r);
    lcd.print(" G:");
    lcd.print(g);
    lcd.setCursor(0, 1); // Siirrä kursori seuraavalle riville
    lcd.print("B:");
    lcd.print(b); // Näytä sininen väriarvo

    // Aseta LCD:n taustavalo RGB-arvojen mukaan
    lcd.setRGB(r >> 8, g >> 8, b >> 8);

    delay(1000); // Odota 1 sekunti ennen seuraavaa lukemista
}
