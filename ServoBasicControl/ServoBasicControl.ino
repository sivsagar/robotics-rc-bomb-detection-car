#include <ESP32Servo.h>

Servo myServo;
const int ledPin = 2;

void setup() {
  myServo.attach(13, 500, 2400); // Use GPIO 13 & adjust pulse range
  pinMode(ledPin, OUTPUT);
  delay(100);  // Stabilization delay
}

void loop() {
  myServo.writeMicroseconds(1000); // Move to 0°
  digitalWrite(ledPin, HIGH);
  delay(1000);

  myServo.writeMicroseconds(1500); // Move to 90°
  digitalWrite(ledPin, LOW);
  delay(1000);

  myServo.writeMicroseconds(2000); // Move to 180°
  digitalWrite(ledPin, HIGH);
  delay(1000);
}
