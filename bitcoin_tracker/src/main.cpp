#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// WiFi-asetukset
const char* ssid = "SOURCE";       
const char* password = "Pelle!23";
WiFiClientSecure wifiClient;


void setup() {
  Serial.begin(115200);  // Avaa sarjayhteys kommunikointia varten

  // Yhdistä WiFi-verkkoon
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  // Odota, että yhteys muodostuu
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  wifiClient.setInsecure();
}


void loop() {
  if (WiFi.status() == WL_CONNECTED) {  // Varmista, että olemme yhteydessä WiFiin
    HTTPClient http;    // Luo HTTPClient-objekti

    // Aloita HTTP-yhteys käyttämällä WiFiClientia ja URL:ia
    String url = "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd";
    http.begin(wifiClient, url);  // Käytetään globaalia WiFiClient-instanssia
    
    int httpResponseCode = http.GET();  // Suorita GET-pyyntö

    if (httpResponseCode > 0) {
      String payload = http.getString();  // Lue vastaus palvelimelta

      Serial.println("HTTP Response code: " + String(httpResponseCode));
      Serial.println("Payload: " + payload);

      // Parsitaan JSON-vastaus
      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, payload);
      if (!error) {
        float bitcoinPrice = doc["bitcoin"]["usd"];
        Serial.println("Bitcoin price (USD): " + String(bitcoinPrice));
      } else {
        Serial.println("Failed to parse JSON");
      }

    } else {
      Serial.println("Error on HTTP request: " + String(httpResponseCode));
    }

    http.end();  // Sulje yhteys
  }

  delay(60000);  // Odota minuutti ennen seuraavaa pyyntöä
}


