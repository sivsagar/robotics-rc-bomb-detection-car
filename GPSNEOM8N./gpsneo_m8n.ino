#include <TinyGPS++.h>
#include <HardwareSerial.h>

// Define the hardware serial port for GPS
HardwareSerial gpsSerial(1);

// Create a TinyGPS++ object
TinyGPSPlus gps;

void setup() {
    Serial.begin(115200);    // Serial monitor
    gpsSerial.begin(9600, SERIAL_8N1, 16, 17);  // GPS module (RX=16, TX=17)
    
    Serial.println("GPS Module Initialized...");
}

void loop() {
    while (gpsSerial.available()) {
        gps.encode(gpsSerial.read());

        if (gps.location.isUpdated()) {
            Serial.print("Latitude: ");
            Serial.print(gps.location.lat(), 6);
            Serial.print(", Longitude: ");
            Serial.println(gps.location.lng(), 6);
        }

        if (gps.speed.isUpdated()) {
            Serial.print("Speed (km/h): ");
            Serial.println(gps.speed.kmph());
        }

        if (gps.satellites.isUpdated()) {
            Serial.print("Satellites: ");
            Serial.println(gps.satellites.value());
        }
    }
}

/*Explanation
->Uses HardwareSerial(1) since ESP32 has multiple hardware UARTs.
->Reads latitude, longitude, speed, and satellite count.
->Uses GPIO 16 (RX2) and GPIO 17 (TX2) for GPS communication.*/