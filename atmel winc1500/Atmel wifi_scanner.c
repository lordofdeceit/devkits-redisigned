#include <SPI.h>
#include <WiFi101.h>
//a simple program using the Atmel WINC1500 Xplained Pro board and the Arduino IDE for linux 
//that displays the available Wi-Fi networks:
void setup() {
  Serial.begin(115200);
  while (!Serial);
  
  Serial.println("Scanning Wi-Fi networks...");

  int numNetworks = WiFi.scanNetworks();
  Serial.print("Found ");
  Serial.print(numNetworks);
  Serial.println(" networks:");

  for (int i = 0; i < numNetworks; i++) {
    Serial.print(i+1);
    Serial.print(": ");
    Serial.print(WiFi.SSID(i));
    Serial.print(" (");
    Serial.print(WiFi.RSSI(i));
    Serial.println(" dBm)");
  }
}

void loop() {
  // Do nothing
}
