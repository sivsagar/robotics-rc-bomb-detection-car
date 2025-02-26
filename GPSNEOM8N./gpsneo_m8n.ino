#include <TinyGPS++.h>
#include <HardwareSerial.h>

TinyGPSPlus gps;
HardwareSerial gpsSerial(1);  // Use UART1

void setup() {
    Serial.begin(115200);
    gpsSerial.begin(9600, SERIAL_8N1, 16, 17);  // GPS RX=16, TX=17
}

void loop() {
    while (gpsSerial.available()) {
        gps.encode(gpsSerial.read());

        if (gps.location.isUpdated()) {
            Serial.print("Lat: "); Serial.print(gps.location.lat(), 6);
            Serial.print(", Lng: "); Serial.println(gps.location.lng(), 6);
        }
    }
}


/*Explanation
->Uses HardwareSerial(1) since ESP32 has multiple hardware UARTs.
->Reads latitude, longitude, speed, and satellite count.
->Uses GPIO 16 (RX2) and GPIO 17 (TX2) for GPS communication.*/