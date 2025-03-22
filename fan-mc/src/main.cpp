#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Controller.h>

#define SSID "Yanuu"
#define PASS "Wkwkwkwk"

Controller *controller;

IPAddress staticIP(192,168,18,36);
IPAddress gatewayIP(192,168,18,1);
IPAddress subnetMask(255,255,255,0);

// Setup code, run once:
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  delay(5000);

  WiFi.mode(WIFI_STA);
  WiFi.config(staticIP, gatewayIP, subnetMask);
  WiFi.begin(SSID, PASS);
  
  short c = 0;
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    Serial.print(".");
    if (c++ >= 10) {
      Serial.println();
      return;
    }
  }

  Serial.printf("Connected to %s.\n", SSID);
  Serial.printf("IP Address: %s", WiFi.localIP().toString().c_str());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  digitalWrite(LED_BUILTIN, LOW);
  delay(500);

  controller = new Controller();

  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
}

// Main code, run repeatedly:
void loop() {
  (*controller).listen();
  MDNS.update();
  delay(300);
}
