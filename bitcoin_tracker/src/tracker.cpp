// #include <ESP8266WiFi.h>
// #include <ESP8266HTTPClient.h>
// #include <ArduinoJson.h>
// #include <Wire.h>
// #include <DFRobot_RGBLCD1602.h>

// const char* ssid = "SOURCE";       
// const char* password = "Pelle!23";

// // Define LCD with RGB address, columns, and rows
// DFRobot_RGBLCD1602 lcd(0x60, 16, 2);  // Adjust the address if necessary

// WiFiClientSecure wifiClient;
// float lastBitcoinPrice = 0.0;  // Variable to store the last Bitcoin price

// void setup() {
//   Serial.begin(115200);  // Initialize serial communication

//   // Initialize the LCD and set an initial RGB backlight color
//   lcd.init();
//   lcd.setRGB(0, 0, 255);  // Set initial color to blue
//   lcd.setCursor(0, 0);
//   lcd.print("Connecting...");

//   // Connect to WiFi
//   WiFi.begin(ssid, password);
//   Serial.print("Connecting to WiFi");

//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.print(".");
//   }
  
//   Serial.println("");
//   Serial.println("Connected to WiFi");
//   Serial.print("IP Address: ");
//   Serial.println(WiFi.localIP());

//   wifiClient.setInsecure();

//   lcd.clear();
//   lcd.setCursor(0, 0);
//   lcd.print("WiFi Connected");
//   delay(2000);
// }

// void loop() {
//   if (WiFi.status() == WL_CONNECTED) {  
//     HTTPClient http;    

//     // API URL
//     String url = "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd";
//     http.begin(wifiClient, url);
    
//     int httpResponseCode = http.GET();

//     if (httpResponseCode > 0) {
//       String payload = http.getString();  

//       Serial.println("HTTP Response code: " + String(httpResponseCode));
//       Serial.println("Payload: " + payload);

//       // Parse JSON response
//       StaticJsonDocument<200> doc;
//       DeserializationError error = deserializeJson(doc, payload);
//       if (!error) {
//         float bitcoinPrice = doc["bitcoin"]["usd"];
//         Serial.println("Bitcoin price (USD): " + String(bitcoinPrice));

//         // Check if the price has increased or decreased
//         if (bitcoinPrice > lastBitcoinPrice) {
//           lcd.setRGB(0, 255, 0);  // Set backlight to green
//         } else if (bitcoinPrice < lastBitcoinPrice) {
//           lcd.setRGB(255, 0, 0);  // Set backlight to red
//         }

//         // Update the display with the new price
//         lcd.clear();
//         lcd.setCursor(0, 0);
//         lcd.print("BTC: $");
//         lcd.print(bitcoinPrice, 2);  // Display with 2 decimal points

//         // Store the current price for the next comparison
//         lastBitcoinPrice = bitcoinPrice;
//       } else {
//         Serial.println("Failed to parse JSON");
//         lcd.clear();
//         lcd.setCursor(0, 0);
//         lcd.print("JSON Parse Error");
//       }
//     } else {
//       Serial.println("Error on HTTP request: " + String(httpResponseCode));
//       lcd.clear();
//       lcd.setCursor(0, 0);
//       lcd.print("HTTP Error: ");
//       lcd.setCursor(0, 1);
//       lcd.print(httpResponseCode);
//     }

//     http.end();
//   }

//   delay(60000);  // Wait for a minute before the next request
// }
// // 