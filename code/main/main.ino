#include <WiFi.h>

int i = 0;

const char *ssid = "esp32test";
const char *password = "1234";

WiFiServer server(80);

void setup() {

  pinMode(2, OUTPUT);
  
  Serial.begin(9600);

  Serial.print("Setting up AP: ");
  Serial.println(ssid);
  
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New client");

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.println(c);
        client.println(c);
        digitalWrite(2, i++%2?LOW:HIGH);
      }
    }
  }
}
