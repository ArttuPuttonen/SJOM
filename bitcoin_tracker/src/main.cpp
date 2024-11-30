#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <DFRobot_RGBLCD1602.h>

const char* ssid = "DNA-WIFI-0266";
const char* password = "14964055";

// Define LCD with RGB address, columns, and rows
DFRobot_RGBLCD1602 lcd(0x60, 16, 2);  // Adjust the address if necessary

WiFiClientSecure wifiClient;
float lastPrice = 0.0;  // Variable to store the last fetched price
bool isBitcoin = true;  // Track which coin is displayed (true = Bitcoin, false = Dogecoin)

// Button pin configuration
const int buttonPin = 0;  // D3 pin on ESP8266
unsigned long lastButtonPress = 0;
const unsigned long debounceDelay = 50;  // Debounce delay for button press

// Update intervals
unsigned long lastPriceUpdate = 0;
const unsigned long priceUpdateInterval = 60000;  // 1 minute interval for price updates

// Messages for the second row, with a placeholder for percentage change
String messages[] = {"UPD every min", "Green: price up", "Red: price down", "Change: +0.000%"};
unsigned int messageIndex = 0;  // Index for cycling through messages
unsigned long lastMessageSwitch = 0;
const unsigned long messageDisplayInterval = 2500;  // 2.5 seconds interval for message rotation

void setup() {
    Serial.begin(115200);  // Initialize serial communication

    // Initialize LCD
    lcd.init();
    lcd.setRGB(255, 255, 255);  // Initial color
    lcd.setCursor(0, 0);
    lcd.print("Connecting...");

    // Configure button pin with internal pull-up resistor
    pinMode(buttonPin, INPUT_PULLUP);

    // Connect to WiFi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    unsigned long wifiTimeout = millis() + 30000;  // 30 sekunnin aikakatkaisu
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
        if (millis() > wifiTimeout) {
            Serial.println("\nWiFi connection failed. Restarting...");
            ESP.restart();  // Uudelleenkäynnistetään laite
        }
    }
    Serial.println("");
    Serial.println("Connected to WiFi");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Connected");

    wifiClient.setInsecure();
    delay(2000);  // Short delay to show the initial message
}

void loop() {
    unsigned long currentMillis = millis();

    // Handle button press to toggle between Bitcoin and Dogecoin
    if (digitalRead(buttonPin) == LOW) {  // Button is pressed
        if (currentMillis - lastButtonPress >= debounceDelay) {
            isBitcoin = !isBitcoin;  // Toggle the coin
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(isBitcoin ? "BTC selected" : "DOGE selected");
            lastPrice = 0.0;  // Reset last price to prevent incorrect change calculation
            delay(500);  // Short delay to show feedback
            lastPriceUpdate = 0;  // Force immediate price update after button press
        }
        lastButtonPress = currentMillis;
    }

    // Update the coin price every 1 minute or immediately after button press
    if (currentMillis - lastPriceUpdate >= priceUpdateInterval || lastPriceUpdate == 0) {
        lastPriceUpdate = currentMillis;

        if (WiFi.status() == WL_CONNECTED) {
            HTTPClient http;
            String url;

            // Select API endpoint based on the selected coin
            if (isBitcoin) {
                url = "https://api.binance.com/api/v3/ticker/price?symbol=BTCUSDT";
            } else {
                url = "https://api.binance.com/api/v3/ticker/price?symbol=DOGEUSDT";
            }

            http.begin(wifiClient, url);
            int httpResponseCode = http.GET();

            if (httpResponseCode > 0) {
                String payload = http.getString();

                // Debugging: Print the full JSON payload
                Serial.println("Full JSON payload:");
                Serial.println(payload);

                // Parse JSON response
                StaticJsonDocument<512> doc;
                DeserializationError error = deserializeJson(doc, payload);
                if (!error) {
                    float currentPrice = doc["price"].as<float>();

                    Serial.println((isBitcoin ? "Bitcoin" : "Dogecoin") + String(" price: $") +
                                   String(currentPrice, isBitcoin ? 2 : 5));

                    // Calculate percentage change
                    float percentageChange = 0.0;
                    if (lastPrice != 0.0) {
                        percentageChange = ((currentPrice - lastPrice) / lastPrice) * 100.0;
                    }

                    // Update the last message in the messages array with the percentage change
                    String changeMessage = "Change: ";
                    if (percentageChange >= 0) {
                        changeMessage += "+";
                    }
                    changeMessage += String(percentageChange, 2) + "%";
                    messages[3] = changeMessage;  // Update the last message

                    // Set backlight color based on price change
                    lcd.setRGB(currentPrice > lastPrice ? 0 : 255, currentPrice > lastPrice ? 255 : 0, 0);  // Green/Red

                    // Display the price on the LCD
                    lcd.setCursor(0, 0);
                    lcd.print("                ");  // Clear the first row
                    lcd.setCursor(0, 0);
                    lcd.print(isBitcoin ? "BTC: $" : "DOGE: $");
                    lcd.print(currentPrice, isBitcoin ? 2 : 5);  // 2 decimals for Bitcoin, 5 for Dogecoin

                    // Store the current price for comparison
                    lastPrice = currentPrice;
                } else {
                    Serial.println("Failed to parse JSON");
                    lcd.setCursor(0, 0);
                    lcd.print("JSON Parse Error");
                }
            } else {
                Serial.println("HTTP request failed with code: " + String(httpResponseCode));
                lcd.setCursor(0, 0);
                lcd.print("HTTP Error: ");
                lcd.setCursor(0, 1);
                lcd.print(httpResponseCode);
            }
            http.end();  // Close HTTP connection
        }
    }

    // Update the second row message every 2.5 seconds
    if (currentMillis - lastMessageSwitch >= messageDisplayInterval) {
        lastMessageSwitch = currentMillis;

        lcd.setCursor(0, 1);
        lcd.print("                ");  // Clear the second row
        lcd.setCursor(0, 1);
        lcd.print(messages[messageIndex]);  // Display the current message

        messageIndex++;
        if (messageIndex >= (sizeof(messages) / sizeof(messages[0]))) {
            messageIndex = 0;  // Loop back to the first message
        }
    }
}
