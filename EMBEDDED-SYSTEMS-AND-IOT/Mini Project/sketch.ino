#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include "DHTesp.h"

char ssid[] = "Riyaz";
char pass[] = "12344321";
WiFiClient client;
unsigned long myChannelNumber = 2516343;
const char * myWriteAPIKey = "V4Z10JCNUTAUA0Q1";
DHTesp dhtSensor;
TempAndHumidity data;
const int DHT_PIN = D2; // Using pin D2 for the DHT11 sensor

int statusCode;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT11); // Configuring DHT11 sensor
}

void loop() {
  connectToWiFi();
  computeData();
  writeData();
  delay(1000);
}

void connectToWiFi(){
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("Attempting to connect to WiFi");
    WiFi.begin(ssid, pass);
    while(WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
    Serial.println("\nConnected to WiFi.");
  }
}

void computeData(){
  data = dhtSensor.getTempAndHumidity();
  Serial.println("-----------");
  Serial.println("Humidity: " + String(data.humidity));
  Serial.println("Temperature: " + String(data.temperature));
  Serial.println("-----------");
}

void writeData(){
  ThingSpeak.setField(1, data.humidity);
  ThingSpeak.setField(2, data.temperature);
  statusCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(statusCode == 200) // Successful writing code
    Serial.println("Channel update successful.");
  else
    Serial.println("Problem writing data. HTTP error code: " + String(statusCode));
  delay(15000); // Data to be uploaded every 15 seconds
}
