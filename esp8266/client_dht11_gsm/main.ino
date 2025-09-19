#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "sensor_mqtt.h"
#include "sms_alert.h"
#include "lcd_display.h"

const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";
const char* mqtt_server = "192.168.1.100";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  setupDHT();
  setupSIM900();
  setupLCD();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  client.setServer(mqtt_server, 1883);
  reconnect();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (!isnan(temperature) && !isnan(humidity)) {
    displaySensorData(temperature, humidity);
    publishSensorData(client);
  } else {
    Serial.println("Failed to read DHT11");
  }
  delay(5000);
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP8266_DHT11")) {
      Serial.println("Connected to MQTT");
    } else {
      delay(5000);
    }
  }
}
