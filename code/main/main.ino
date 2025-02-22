#include <WiFi.h>

#define LEAD

int i = 0;

#define WIFI_SSID "strandbeest_ap"
#define WIFI_PSK  "12345678"

#ifdef LEAD
WiFiServer server(80);
#else
#endif

void setupAP() {
  Serial.print("Setting up AP: ");
  Serial.println(WIFI_SSID);
  
  WiFi.softAP(WIFI_SSID, WIFI_PSK);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
}

void setup() {

  pinMode(2, OUTPUT);
  
  Serial.begin(9600);

#ifdef LEAD
  setupAP();
  server.begin();
#endif

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
