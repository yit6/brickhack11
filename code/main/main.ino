#include <WiFi.h>
#include <WebServer.h>

#define LEAD

int i = 0;

#define WIFI_SSID "strandbeest_ap"
#define WIFI_PSK  "12345678"

#ifdef LEAD
WebServer server(80);
#else
#endif

void setupAP() {
  Serial.print("Setting up AP: ");
  Serial.println(WIFI_SSID);
  
  WiFi.softAP(WIFI_SSID, WIFI_PSK);

  delay(1000);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
}

void setup() {

  pinMode(2, OUTPUT);
  
  Serial.begin(9600);

  server.on("/", handle_OnConnect);

#ifdef LEAD
  setupAP();
  server.begin();
#endif

}

void loop() {
  server.handleClient();
}

void handle_OnConnect() {
  Serial.println("connection");
  server.send(200,"text/html","<h1>Hello!</h1>");
}
