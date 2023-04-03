#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

// Set pins for SoftwareSerial communication
const int rxPin = 2;
const int txPin = 3;

// Set up software serial
SoftwareSerial espSerial(rxPin, txPin);

void setup() {
  Serial.begin(9600);
  espSerial.begin(115200);
  delay(1000);
  
  // Connect to Wi-Fi module
  Serial.println("Connecting to Wi-Fi module...");
  espSerial.println("AT");
  delay(1000);
  if (espSerial.find("OK")) {
    Serial.println("Wi-Fi module is ready!");
  } else {
    Serial.println("Error: Wi-Fi module not responding.");
    while(1);
  }

  // Set Wi-Fi mode to client
  Serial.println("Setting Wi-Fi mode to client...");
  espSerial.println("AT+CWMODE=1");
  delay(1000);
  if (espSerial.find("OK")) {
    Serial.println("Wi-Fi mode set to client.");
  } else {
    Serial.println("Error setting Wi-Fi mode.");
    while(1);
  }
  
}

void loop() {
  // Scan for available Wi-Fi networks
  Serial.println("Scanning for available Wi-Fi networks...");
  espSerial.println("AT+CWLAP");
  delay(5000);
  
  // Print list of available Wi-Fi networks
  while(espSerial.available() > 0) {
    String line = espSerial.readStringUntil('\n');
    if (line.indexOf("+CWLAP:") != -1) {
      Serial.println(line);
    }
  }

  delay(10000);
}
