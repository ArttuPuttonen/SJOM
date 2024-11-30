#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <DFRobot_RGBLCD1602.h>
#include <EEPROM.h>

const char* ssid = "wifi name here";
const char* password = "password here";

// Define LCD with RGB address, columns, and rows
DFRobot_RGBLCD1602 lcd(0x60, 16, 2);

WiFiClientSecure wifiClient;

float lastBTCPrice = 0.0;  // Store last BTC price
float lastDOGEPrice = 0.0; // Store last DOGE price
bool isBitcoin = true;     // Track which coin is displayed (true = Bitcoin, false = Dogecoin)
unsigned int timeInterval = 0;  // 0 = 15m, 1 = 1h, 2 = 24h

// Button configuration
#define BUTTON_PIN 0  // GPIO0 (D3 pin on ESP8266)
#define READ_GPIO(pin) ((GPI & (1 << pin)) == 0)  // Macro to read GPIO state
unsigned long lastButtonPress = 0;
bool buttonState = false;

// Update intervals
unsigned long lastPriceUpdate = 0;
const unsigned long priceUpdateInterval = 60000;  // Update prices every 1 minute

// Messages for the second row
String messages[] = {"UPD every min", "Change: +0.00%"};
unsigned int messageIndex = 0;
unsigned long lastMessageSwitch = 0;
const unsigned long messageDisplayInterval = 2500;  // Rotate messages every 2.5 seconds

// Constants for button press durations
const unsigned long debounceDelay = 50;    // Debounce delay
const unsigned long longPressDuration = 700; // Long press threshold

void setup() {
    Serial.begin(115200);
    EEPROM.begin(512);  // Initialize EEPROM with 512 bytes

    // Enable watchdog with an 8-second timeout
    ESP.wdtEnable(WDTO_8S);

    // Load last selected coin and interval from EEPROM
    EEPROM.get(0, isBitcoin);
    EEPROM.get(1, timeInterval);

    // Initialize LCD
    lcd.init();
    lcd.setRGB(255, 255, 255);  // White backlight
    lcd.setCursor(0, 0);
    lcd.print("Connecting...");

    // Configure button pin as input with internal pull-up resistor
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        lcd.setCursor(0, 0);
        lcd.print("WiFi Connecting");
        Serial.print(".");
        ESP.wdtFeed();  // Reset watchdog during long operations
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Connected");

    wifiClient.setInsecure();  // For HTTPS requests
    delay(2000);  // Short delay to show the initial message
}

void loop() {
    ESP.wdtFeed();  // Reset the watchdog timer to prevent restart

    unsigned long currentMillis = millis();

    // Handle button press logic
    if (READ_GPIO(BUTTON_PIN)) {  // Button is pressed
        if (!buttonState && (currentMillis - lastButtonPress > debounceDelay)) {
            lastButtonPress = currentMillis;
            buttonState = true;
        }
    } else {  // Button is released
        if (buttonState) {
            unsigned long pressDuration = currentMillis - lastButtonPress;

            if (pressDuration < longPressDuration) {
                // Short press: Toggle between Bitcoin and Dogecoin
                isBitcoin = !isBitcoin;
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print(isBitcoin ? "BTC selected" : "DOGE selected");

                // Save the selected coin to EEPROM
                EEPROM.put(0, isBitcoin);
                EEPROM.commit();
            } else {
                // Long press: Change time interval (15m ↔ 1h ↔ 24h)
                timeInterval = (timeInterval + 1) % 3;
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Interval: ");
                lcd.print(timeInterval == 0 ? "15m" : (timeInterval == 1 ? "1h" : "24h"));

                // Save the selected interval to EEPROM
                EEPROM.put(1, timeInterval);
                EEPROM.commit();
            }

            buttonState = false;
            lastPriceUpdate = 0;  // Force immediate price update after button press
        }
    }

    // Update the coin price every 1 minute or immediately after button press
    if (currentMillis - lastPriceUpdate >= priceUpdateInterval || lastPriceUpdate == 0) {
        lastPriceUpdate = currentMillis;

        if (WiFi.status() == WL_CONNECTED) {
            HTTPClient http;
            String url;
            String interval;

            // Set interval for historical data
            if (timeInterval == 0) interval = "15m";
            else if (timeInterval == 1) interval = "1h";
            else interval = "1d";  // Binance uses 1d for daily interval

            // Select API endpoint based on the selected coin
            String symbol = isBitcoin ? "BTCUSDT" : "DOGEUSDT";
            url = "https://api.binance.com/api/v3/klines?symbol=" + symbol + "&interval=" + interval + "&limit=1";

            http.begin(wifiClient, url);
            int httpResponseCode = http.GET();

            if (httpResponseCode > 0) {
                String payload = http.getString();

                // Parse JSON response
                StaticJsonDocument<1024> doc;
                DeserializationError error = deserializeJson(doc, payload);
                if (!error) {
                    float currentPrice = doc[0][4].as<float>();  // Closing price
                    float openPrice = doc[0][1].as<float>();     // Opening price

                    Serial.println((isBitcoin ? "Bitcoin" : "Dogecoin") + String(" price: $") +
                                   String(currentPrice, isBitcoin ? 2 : 5));

                    // Calculate percentage change
                    float percentageChange = 0.0;
                    if (openPrice != 0.0) {
                        percentageChange = ((currentPrice - openPrice) / openPrice) * 100.0;
                    }

                    // Update the last message in the messages array with the percentage change
                    String changeMessage = "Change: ";
                    if (percentageChange >= 0) {
                        changeMessage += "+";
                    }
                    changeMessage += String(percentageChange, 2) + "%";
                    messages[1] = changeMessage;  // Update the "Change" message

                    // Set backlight color based on price change
                    lcd.setRGB(currentPrice > openPrice ? 0 : 255, currentPrice > openPrice ? 255 : 0, 0);  // Green/Red

                    // Display the price on the LCD
                    lcd.setCursor(0, 0);
                    lcd.print("                ");  // Clear the first row
                    lcd.setCursor(0, 0);
                    lcd.print(isBitcoin ? "BTC: $" : "DOGE: $");
                    lcd.print(currentPrice, isBitcoin ? 2 : 5);  // 2 decimals for Bitcoin, 5 for Dogecoin
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