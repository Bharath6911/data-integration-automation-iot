#ifndef SMS_ALERT_H
#define SMS_ALERT_H
#include <SoftwareSerial.h>

#define RX_PIN D7
#define TX_PIN D8
SoftwareSerial sim900(RX_PIN, TX_PIN);

void setupSIM900() {
  sim900.begin(9600);
}

void sendSMS(String number, String message) {
  sim900.println("AT+CMGF=1");
  delay(1000);
  sim900.print("AT+CMGS=\"");
  sim900.print(number);
  sim900.println("\"");
  delay(1000);
  sim900.print(message);
  delay(1000);
  sim900.write(26);
  delay(3000);
}
#endif
