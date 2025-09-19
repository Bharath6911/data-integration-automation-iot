#ifndef SENSOR_MQTT_H
#define SENSOR_MQTT_H
#include <DHT.h>
#include <PubSubClient.h>
#include "sms_alert.h"

#define DHTPIN 2
#define DHTTYPE DHT11
#define TEMP_THRESHOLD 37

DHT dht(DHTPIN, DHTTYPE);

void setupDHT() {
  dht.begin();
}

void publishSensorData(PubSubClient &client) {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(t) || isnan(h)) return;

  String payload = "{\"temperature\":" + String(t) + ",\"humidity\":" + String(h) + "}";
  client.publish("esp8266/dht11", payload.c_str());

  if (t > TEMP_THRESHOLD) {
    sendSMS("Your_Number", "ALERT: Temperature exceeded threshold!");
  }
}
#endif
