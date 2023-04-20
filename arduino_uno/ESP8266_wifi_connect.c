#include <ESP8266WiFi.h>
//This code connects to a WiFi network with a specified SSID and password, and then sends an HTTP request to a specified server. 
//You will need to modify the ssid, password, and connect lines to match your network configuration.
const char* ssid = "your_SSID_here";
const char* password = "your_PASSWORD_here";

void setup() {
  Serial.begin(9600);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Send HTTP request
  WiFiClient client;

  const int httpPort = 80;
  if (!client.connect("example.com", httpPort)) {
    Serial.println("connection failed");
    return;
  }

  client.print(String("GET /index.html HTTP/1.1\r\n") +
               "Host: example.com\r\n" +
               "Connection: close\r\n\r\n");

  // Wait for response
  while (client.connected()) {
    if (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }

  Serial.println();
  Serial.println("closing connection");
}
