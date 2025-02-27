#include <Arduino.h>

// Metal Detector Input Pin
#define METAL_DETECTOR_PIN 35

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Metal Detector Sensor Value : ");
  Serial.println(getMetalDetectorValue());
}

int getMetalDetectorValue() {
  int analogValue = analogRead(METAL_DETECTOR_PIN);  // Read raw analog Input
  int mappedValue = map(analogValue, 0, 4095, 0, 100);  // Map to 0-100 range

  //int mappedValue = random(10, 100);
  return mappedValue;  // Return mapped value
}

