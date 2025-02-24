#define FOLLOW

#include <WiFi.h>
#include <Stepper.h>

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

#define STEPS_PER_REVOLUTION 2048

Stepper left(STEPS_PER_REVOLUTION, 12, 27, 14, 26);
Stepper right(STEPS_PER_REVOLUTION, 35, 32, 33, 25);

int ur, dr, ul, dl = 0;

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
  server.on("/upRight", upRight);
  server.on("/downRight", downRight);
  server.on("/upLeft", upLeft);
  server.on("/downLeft", downLeft);
  server.on("/upRightN", upRightN);
  server.on("/downRightN", downRightN);
  server.on("/upLeftN", upLeftN);
  server.on("/downLeftN", downLeftN);
#else
  setupStation();
#endif
  left.setSpeed(4);
  right.setSpeed(2);
}

void loop() {
  
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

  left.step(ul - dl);
  right.step(ur - dr);
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
  ur = 1;
  server.send(200, "text/plain", "Up Right On");
}

void downRight() {
  dr = 1;
  server.send(200, "text/plain", "Down Right On");
}

void upLeft() {
  ul = 1;
  server.send(200, "text/plain", "Up Left On");
}

void downLeft() {
  dl = 1;
  server.send(200, "text/plain", "Down Left On");
}

void upRightN() {
  ur = 0;
  server.send(200, "text/plain", "Up Right Off");
}

void downRightN() {
  dr = 0;
  server.send(200, "text/plain", "Down Right Off");
}

void upLeftN() {
  ul = 0;
  server.send(200, "text/plain", "Up Left Off");
}

void downLeftN() {
  dl = 0;
  server.send(200, "text/plain", "Down Left Off");
}
