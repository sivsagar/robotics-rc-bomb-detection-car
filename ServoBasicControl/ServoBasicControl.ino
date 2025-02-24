#include <ESP32Servo.h>

Servo myServo;

void setup() {
  myServo.attach(13);  // Connect servo signal to GPIO 13
}

void loop() {
  myServo.write(0);    // Move to 0°
  delay(500);
  
  myServo.write(180);  // Move to 180°
  delay(500);
}
