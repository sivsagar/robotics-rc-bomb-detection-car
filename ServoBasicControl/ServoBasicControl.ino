#include <ESP32Servo.h>

Servo myServo;

void setup() {
  myServo.attach(13);  // Connect servo signal to GPIO 13
}

void loop() {
  for(int i=60;i<=120;i++) {
    myServo.write(i);
    delay(10);
  }
  delay(1000);
  for(int i=120;i>=60;i--) {
    myServo.write(i);
    delay(10);
  }
  delay(1000);
}
