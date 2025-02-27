#include <ESP32Servo.h>

Servo myServo;

// Steering Angle
#define LEFT_ANGLE 60
#define MIDDLE_ANGLE 90
#define RIGHT_ANGLE 140

void setup() {
  Serial.begin(115200);
  myServo.attach(13);  // Connect servo signal to GPIO 13
}

void loop() {
  myServo.write(LEFT_ANGLE);
  Serial.println(LEFT_ANGLE);
  delay(1000);
  myServo.write(MIDDLE_ANGLE);
  Serial.println(MIDDLE_ANGLE);
  delay(1000);
  myServo.write(RIGHT_ANGLE);
  Serial.println(RIGHT_ANGLE);
  delay(1000);
}