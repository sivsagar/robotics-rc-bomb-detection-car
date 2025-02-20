#include <ESP32Servo.h>

Servo myServo;  // Create a servo object

void setup() {
    myServo.attach(13);  // Attach servo to GPIO 13
}

void loop() {
    for (int pos = 0; pos <= 180; pos++) {  // Move from 0° to 180°
        myServo.write(pos);
        delay(15);
    }
    for (int pos = 180; pos >= 0; pos--) {  // Move from 180° to 0°
        myServo.write(pos);
        delay(15);
    }
}
