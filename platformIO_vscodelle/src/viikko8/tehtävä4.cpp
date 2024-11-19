// #include <Arduino.h>
// #include <Wire.h>
// #include <DFRobot_RGBLCD1602.h>

// // Määritä I2C-osoite ja näytön koko
// DFRobot_RGBLCD1602 lcd(0x27, 16, 2); // Muuta osoite tarvittaessa

// void setup() {
//   Serial.begin(9600);
//   Serial.println("Write something to the serial monitor.");

//   lcd.init();  // Alustaa LCD-näytön
//   lcd.clear(); // Tyhjentää näytön
// }

// void loop() {
//   if (Serial.available() > 0) {
//     String message = Serial.readStringUntil('\n'); 
//     Serial.print("Message received, content: ");  
//     Serial.println(message);
    
//     // Etsi "Print" komento
//     int pos_s = message.indexOf("Print");
    
//     if (pos_s > -1) {
//       Serial.println("Command = Print ");
//       pos_s = message.indexOf(":");

//       if (pos_s > -1) {
//         String stat = message.substring(pos_s + 1);
        
//         // Tarkista, onko stat tyhjää
//         if (stat.length() > 0) {
//           // Näytä LCD-näytöllä
//           lcd.clear(); // Tyhjennä LCD-näyttö ennen uuden viestin näyttämistä
//           lcd.print(stat); // Tulosta viesti LCD-näytölle
//           Serial.print("LCD display updated with: ");
//           Serial.println(stat); // Ilmoita sarjamonitorissa
//         }
//         else {
//           Serial.println("No message to print on LCD.");
//         }
//       }  
//     }
//     else {
//       Serial.println("No command found, try typing Print:<message>\n");
//     }
//   }
// }
