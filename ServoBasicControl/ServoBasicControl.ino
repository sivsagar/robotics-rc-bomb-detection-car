#include <ESP32Servo.h>

Servo myServo;

void setup() {
  Serial.begin(115200);
  myServo.attach(13);  // Connect servo signal to GPIO 13
}

void loop() {
  myServo.write(60);
  Serial.println(60);
  delay(1000);
  myServo.write(140);
  Serial.println(140);
  delay(1000);
}