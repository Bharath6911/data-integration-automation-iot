#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "buzzer.h"

const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";
const char* mqtt_server = "192.168.1.100";

const int trigPin = 5;
const int echoPin = 4;
const int buzzerPin = 0;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  client.setServer(mqtt_server, 1883);
  reconnect();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343) / 2;

  String payload = "{\"distance\":" + String(distance) + "}";
  client.publish("esp8266/ultrasonic", payload.c_str());

  if (distance < 50) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }
  delay(5000);
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP8266_Ultrasonic")) {
      Serial.println("Connected to MQTT");
    } else {
      delay(5000);
    }
  }
}
