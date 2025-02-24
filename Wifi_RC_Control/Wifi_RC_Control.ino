#include <WiFi.h>
#include <WebSocketsServer.h>

const char* ssid = "PRITAMPC-Hotspot";
const char* password = "2x8690+G";

WebSocketsServer webSocket(81);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  String command = String((char*)payload);

  if (command == "forward") {
    Serial.println("Moving Forward");
  } else if (command == "backward") {
    Serial.println("Moving Backward");
  } else if (command == "left") {
    Serial.println("Turning Left");
  } else if (command == "right") {
    Serial.println("Turning Right");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(1000); Serial.println("Connecting..."); }

  Serial.println("Connected! ESP32 IP: " + WiFi.localIP().toString());
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();

  int sensorValue = random(10, 100); // Simulated sensor value
  String sensorData = "Sensor: " + String(sensorValue);

  webSocket.broadcastTXT(sensorData);
  delay(1000); 
}
