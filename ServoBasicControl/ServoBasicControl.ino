#include <ESP32Servo.h>

Servo myServo;

int angle_difference = 20;

void setup() {
  Serial.begin(115200);
  myServo.attach(13);  // Connect servo signal to GPIO 13
}

void loop() {
  myServo.write(90+angle_difference);
  delay(1000);
  myServo.write(90-angle_difference);
  delay(1000);
}