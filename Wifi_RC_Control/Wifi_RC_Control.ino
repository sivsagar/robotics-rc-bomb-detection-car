#include <WiFi.h>
#include <WebSocketsServer.h>
#include <ESP32Servo.h>
#include <Arduino.h>

const char* ssid = "PRITAMPC-Hotspot";
const char* password = "2x8690+G";

int speed = 127;

// Motor Driver Pins
#define STEERING 13
#define ENA 14
#define IN1 27
#define IN2 26
#define ENB 25
#define IN3 33
#define IN4 32

// Metal Detector Input Pin
#define METAL_DETECTOR_PIN 35

WebSocketsServer webSocket(81);
Servo myServo;

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  String command = String((char*)payload);

  if (command == "forward") {
    Serial.println("Moving Forward");
    moveForward();
  } else if (command == "backward") {
    Serial.println("Moving Backward");
    moveBackward();
  } else if (command == "left") {
    Serial.println("Turning Left");
  } else if (command == "right") {
    Serial.println("Turning Right");
  } else if (command == "stop") {
    Serial.println("Stop Movement");
    stopCar();
  } else {
    int speedSliderValue = command.toInt();
    speed = map(speedSliderValue, 0, 100, 0, 255);
    Serial.print("Speed : ");
    Serial.println(speed);
  }
}

void setup() {
  Serial.begin(115200);

  // Setup Motor Driver Pins as Output
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  myServo.attach(STEERING);  // Connect servo signal to GPIO 13

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(1000); Serial.println("Connecting..."); }

  Serial.println("Connected! ESP32 IP: " + WiFi.localIP().toString());
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();

  String metalDetectorData = "metal-detector-value: " + String(getMetalDetectorValue());

  webSocket.broadcastTXT(metalDetectorData);
  delay(50); 
}

int getMetalDetectorValue() {
  //int analogValue = analogRead(METAL_DETECTOR_PIN);  // Read raw analog Input
  //int mappedValue = map(analogValue, 0, 4095, 0, 100);  // Map to 0-100 range

  int mappedValue = random(10, 100);
  return mappedValue;  // Return mapped value
}


void moveForward() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
}

void moveBackward() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
}

void stopCar() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
}

void steerLeft() {
  myServo.write(60);
}

void steerRight() {
  myServo.write(120);
}