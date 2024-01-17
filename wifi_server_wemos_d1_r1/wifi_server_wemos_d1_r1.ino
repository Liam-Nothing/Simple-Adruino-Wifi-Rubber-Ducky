#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "Wifi-Bad-USB";
const char *password = "123456789";

ESP8266WebServer server(80);

const int additionalPins[] = {5, 4, 14, 12, 13};
const int numAdditionalPins = 5;
bool ledState = LOW;
unsigned int numClients = 0;

void handleRoot() {
  String html = "<h1>You are connected</h1>";
  html += "<p><a href=\"/payload1\">Send payload1 (1 1 1 1 1)</a></p>";
  server.send(200, "text/html", html);
}

void handlePayload1() {
  for (int i = 0; i < numAdditionalPins; i++) {
    digitalWrite(additionalPins[i], HIGH);
  }
  Serial.println("PAYLOAD1");
  String html = "<html><head>";
  html += "<meta http-equiv='refresh' content='2;url=/'></head>";
  html += "<body><h1>Waiting...</h1></body></html>";
  server.send(200, "text/html", html);
  delay(200);
  for (int i = 0; i < numAdditionalPins; i++) {
    digitalWrite(additionalPins[i], LOW);
  }
}

void setup() {
  for (int i = 0; i < numAdditionalPins; i++) {
    digitalWrite(additionalPins[i], LOW);
  }
  for (int i = 0; i < numAdditionalPins; i++) {
    pinMode(additionalPins[i], OUTPUT);
    digitalWrite(additionalPins[i], ledState);
  }
  delay(1000);
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println(" ");
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/payload1", handlePayload1);
  server.begin();
}

void loop() {
  server.handleClient();
  unsigned int currentNumClients = WiFi.softAPgetStationNum();
  if (currentNumClients != numClients) {
    numClients = currentNumClients;
    Serial.print("Number of clients connected: ");
    Serial.println(numClients);
    struct station_info *stationList = wifi_softap_get_station_info();
    while(stationList) {
      Serial.print("Client MAC: ");
      Serial.println(MAC2Str(stationList->bssid));
      stationList = STAILQ_NEXT(stationList, next);
    }
    wifi_softap_free_station_info();
  }
}

String MAC2Str(const uint8_t* mac) {
  char macStr[18] = {0};
  sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(macStr);
}
