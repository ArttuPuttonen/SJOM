#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <DFRobot_RGBLCD1602.h>
#include <EEPROM.h>

const char* ssid = "DNA-WIFI-0266";
const char* password = "14964055";

// Define LCD with RGB address, columns, and rows
DFRobot_RGBLCD1602 lcd(0x60, 16, 2);  // Adjust the address if necessary

WiFiClientSecure wifiClient;
float lastBTCPrice = 0.0;  // Store last BTC price
float lastDOGEPrice = 0.0; // Store last DOGE price
bool isBitcoin = true;     // Track which coin is displayed (true = Bitcoin, false = Dogecoin)

// Button pin configuration
#define BUTTON_PIN 0  // GPIO0 (D3 pin on ESP8266)
unsigned long lastButtonPress = 0;
const unsigned long debounceDelay = 50;  // Debounce delay for button press

#define READ_GPIO(pin) ((GPI & (1 << pin)) == 0)  // Macro to read GPIO state

// Update intervals
unsigned long lastPriceUpdate = 0;
const unsigned long priceUpdateInterval = 60000;  // 1 minute interval for price updates

// Messages for the second row, with a placeholder for percentage change
String messages[] = {"UPD every min", "Green: price up", "Red: price down", "Change: +0.00%"};
unsigned int messageIndex = 0;  // Index for cycling through messages
unsigned long lastMessageSwitch = 0;
const unsigned long messageDisplayInterval = 2500;  // 2.5 seconds interval for message rotation

void setup() {
    Serial.begin(115200);  // Initialize serial communication
    EEPROM.begin(512);     // Initialize EEPROM with 512 bytes

    // Enable watchdog with an 8-second timeout
    ESP.wdtEnable(WDTO_8S);

    // Load last used coin from EEPROM
    EEPROM.get(0, isBitcoin);

    // Initialize LCD
    lcd.init();
    lcd.setRGB(255, 255, 255);  // Initial color
    lcd.setCursor(0, 0);
    lcd.print("Connecting...");

    // Configure button pin as input with internal pull-up resistor
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // Connect to WiFi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    unsigned long wifiTimeout = millis() + 30000;  // 30-second timeout
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
        ESP.wdtFeed();  // Reset the watchdog during long operations
        if (millis() > wifiTimeout) {
            Serial.println("\nWiFi connection failed. Restarting...");
            ESP.restart();  // Restart the device
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
    ESP.wdtFeed();  // Reset the watchdog timer to prevent restart

    unsigned long currentMillis = millis();

    // Handle button press to toggle between Bitcoin and Dogecoin
    if (READ_GPIO(BUTTON_PIN)) {  // Button is pressed
        if (currentMillis - lastButtonPress >= debounceDelay) {
            isBitcoin = !isBitcoin;  // Toggle the coin
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(isBitcoin ? "BTC selected" : "DOGE selected");

            // Save the selected coin to EEPROM
            EEPROM.put(0, isBitcoin);
            EEPROM.commit();

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

                // Parse JSON response
                StaticJsonDocument<512> doc;
                DeserializationError error = deserializeJson(doc, payload);
                if (!error) {
                    float currentPrice = doc["price"].as<float>();

                    Serial.println((isBitcoin ? "Bitcoin" : "Dogecoin") + String(" price: $") +
                                   String(currentPrice, isBitcoin ? 2 : 5));

                    // Calculate percentage change
                    float lastSavedPrice = isBitcoin ? lastBTCPrice : lastDOGEPrice;
                    float percentageChange = 0.0;
                    if (lastSavedPrice != 0.0) {
                        percentageChange = ((currentPrice - lastSavedPrice) / lastSavedPrice) * 100.0;
                    }

                    // Update the last message in the messages array with the percentage change
                    String changeMessage = "Change: ";
                    if (percentageChange >= 0) {
                        changeMessage += "+";
                    }
                    changeMessage += String(percentageChange, 2) + "%";
                    messages[3] = changeMessage;  // Update the last message

                    // Set backlight color based on price change
                    lcd.setRGB(currentPrice > lastSavedPrice ? 0 : 255, currentPrice > lastSavedPrice ? 255 : 0, 0);  // Green/Red

                    // Display the price on the LCD
                    lcd.setCursor(0, 0);
                    lcd.print("                ");  // Clear the first row
                    lcd.setCursor(0, 0);
                    lcd.print(isBitcoin ? "BTC: $" : "DOGE: $");
                    lcd.print(currentPrice, isBitcoin ? 2 : 5);  // 2 decimals for Bitcoin, 5 for Dogecoin

                    // Update the last saved price
                    if (isBitcoin) {
                        lastBTCPrice = currentPrice;
                    } else {
                        lastDOGEPrice = currentPrice;
                    }
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
 