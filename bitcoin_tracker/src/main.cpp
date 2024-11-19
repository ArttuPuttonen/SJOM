#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <DFRobot_RGBLCD1602.h>

const char* ssid = "SOURCE";       
const char* password = "Pelle!23";

// Define LCD with RGB address, columns, and rows
DFRobot_RGBLCD1602 lcd(0x60, 16, 2);  // Adjust the address if necessary

WiFiClientSecure wifiClient;
float lastBitcoinPrice = 0.0;  // Variable to store the last Bitcoin price

// Messages for the second row, with a placeholder for percentage change
String messages[] = {"UPD every min", "Green: price up", "Red: price down", ""};
unsigned int messageIndex = 0;  // Index for cycling through messages

unsigned long lastPriceUpdate = 0;
unsigned long lastMessageSwitch = 0;
const unsigned long priceUpdateInterval = 60000;         // 1 minute interval for price update
const unsigned long messageDisplayInterval = 2500; 

void setup() {
  Serial.begin(115200);  // Initialize serial communication

  // Initialize the LCD and set an initial RGB backlight color
  lcd.init();
  lcd.setRGB(255, 255, 255);  // Set initial color to blue
  lcd.setCursor(0, 0);
  lcd.print("Connecting...");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  wifiClient.setInsecure();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");

  // Display a "Fetching Price..." message immediately after WiFi connects
  lcd.setCursor(0, 1);
  lcd.print("Fetching Price...");
  delay(2000);  // Short delay to show the message before the first update
}

void loop() {
  unsigned long currentMillis = millis();

  // Update the Bitcoin price every 1 minute
  if (currentMillis - lastPriceUpdate >= priceUpdateInterval || lastPriceUpdate == 0) {
    lastPriceUpdate = currentMillis;

    if (WiFi.status() == WL_CONNECTED) {  
      HTTPClient http;    

      // API URL
      String url = "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd";
      http.begin(wifiClient, url);
      
      int httpResponseCode = http.GET();

      if (httpResponseCode > 0) {
        String payload = http.getString();  

        Serial.println("HTTP Response code: " + String(httpResponseCode));
        Serial.println("Payload: " + payload);

        // Parse JSON response
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, payload);
        if (!error) {
          float bitcoinPrice = doc["bitcoin"]["usd"];
          Serial.println("Bitcoin price (USD): " + String(bitcoinPrice));

          // Calculate percentage change
          float percentageChange = 0.0;
          if (lastBitcoinPrice != 0) {
            percentageChange = ((bitcoinPrice - lastBitcoinPrice) / lastBitcoinPrice) * 100;
          }

          // Update the "Change" message with the new percentage change
          String changeMessage = "Change: ";
          if (percentageChange >= 0) {
            changeMessage += "+";
          }
          changeMessage += String(percentageChange, 2) + "%";
          messages[3] = changeMessage;  // Update the last message in the array

          // Set backlight color based on price change
          if (bitcoinPrice > lastBitcoinPrice) {
            lcd.setRGB(0, 255, 0);  // Set backlight to green
          } else if (bitcoinPrice < lastBitcoinPrice) {
            lcd.setRGB(255, 0, 0);  // Set backlight to red
          }

          // Display only the Bitcoin price on the first row
          lcd.setCursor(0, 0);
          lcd.print("                ");  // Clear the first row
          lcd.setCursor(0, 0);
          lcd.print("BTC: $");
          lcd.print(int(bitcoinPrice));  // Display price as integer (no cents)

          // Store the current price for the next comparison
          lastBitcoinPrice = bitcoinPrice;
        } else {
          Serial.println("Failed to parse JSON");
          lcd.setCursor(0, 0);
          lcd.print("JSON Parse Error ");
        }
      } else {
        Serial.println("Error on HTTP request: " + String(httpResponseCode));
        lcd.setCursor(0, 0);
        lcd.print("HTTP Error: ");
        lcd.setCursor(0, 1);
        lcd.print(httpResponseCode);
      }

      http.end();
    }
  }

  // Update the second row message every 2.5 seconds
  if (currentMillis - lastMessageSwitch >= messageDisplayInterval) {
    lastMessageSwitch = currentMillis;

    // Display the current message on the second row
    lcd.setCursor(0, 1);
    lcd.print("                ");  // Clear the second row
    lcd.setCursor(0, 1);
    lcd.print(messages[messageIndex]);

    // Move to the next message
    messageIndex++;
    if (messageIndex >= (sizeof(messages) / sizeof(messages[0]))) {
      messageIndex = 0;  // Loop back to the first message
    }
  }
}
