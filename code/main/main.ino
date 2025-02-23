#define FOLLOW

#include <WiFi.h>

#define LEAD

#ifdef LEAD
#include <WebServer.h>
#else
#include <HTTPClient.h>
#endif

int i = 0;

#define WIFI_SSID "strandbeest_ap"
#define WIFI_PSK  "12345678"

#ifdef LEAD
WebServer server(80);
#else
//HTTPClient http;
#endif

unsigned long next;

const char* html = 
#include "index.html"
;

const char* css =
#include "index.css"
;

const char* js =
#include "index.js"
;

void setupAP() {
  Serial.print("Setting up AP: ");
  Serial.println(WIFI_SSID);
  
  WiFi.softAP(WIFI_SSID, WIFI_PSK);

  delay(1000);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
}

void setupStation() {
  Serial.print("Connecting to: ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PSK);

  while(WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting");
    delay(100);
  }

  Serial.println("Connected");

  next = millis();
}

void setup() {

  pinMode(2, OUTPUT);
  
  Serial.begin(115200);

#ifdef LEAD
  setupAP();
  server.begin();
  server.on("/", handle_OnConnect);
  server.on("/index.css", handleCss);
  server.on("/index.js", handleJs);
#else
  setupStation();
#endif

}

void loop() {
  
  next += 100;

  Serial.println("Loop!");
  
#ifdef LEAD
  server.handleClient();
#else
  HTTPClient http;
  http.begin("http://192.168.4.1/");
  int code = http.GET();

  if (code == HTTP_CODE_OK) {
    Serial.println(http.getString());
  } else {
    Serial.printf(":( code was %d\n", code);
  }
#endif

  while (millis() < next) {
    delay(1);
  }

  next = millis();
}

void handle_OnConnect() {
  Serial.println("connection");
#ifdef LEAD
  server.send(200,"text/html",html);
#endif
}

void handleCss() {
 server.send(200,"text/css",css); 
}

void handleJs() {
  server.send(200, "text/javascript",js);
}

void upRight() {

}

void downRight() {

}

void upLeft() {

}

void downLeft() {

}

void upRightN() {

}

void downRightN() {

}

void upLeftN() {

}

void downLeftN() {

}
