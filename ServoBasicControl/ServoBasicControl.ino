#include <ESP32Servo.h>

Servo myServo;

void setup() {
  Serial.begin(115200);
  myServo.attach(13);  // Connect servo signal to GPIO 13
}

void loop() {
  myServo.write(0);
  Serial.println(0);
  delay(1000);
  myServo.write(35);
  Serial.println(35);
  delay(1000);
}