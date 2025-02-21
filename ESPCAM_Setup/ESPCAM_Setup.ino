#define MQ135_PIN 34  // Connect MQ-135 Analog Output (AO) to GPIO 34

void setup() {
    Serial.begin(115200);
}

void loop() {
    int gasValue = analogRead(MQ135_PIN);  // Read gas sensor value
    Serial.print("MQ-135 Sensor Value: ");
    Serial.println(gasValue);

    delay(1000);  // Read every second
}