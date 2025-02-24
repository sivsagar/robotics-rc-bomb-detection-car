#include <WiFi.h>
#include "esp_camera.h"
#include <WebServer.h>

// 🔹 Replace with your PC hotspot credentials
const char* ssid = "PRITAMPC-Hotspot";
const char* password = "2x8690+G";

// 🔹 AI-Thinker Camera Pins
#define PWDN_GPIO     -1
#define RESET_GPIO    -1
#define XCLK_GPIO     0
#define SIOD_GPIO     26
#define SIOC_GPIO     27

#define Y9_GPIO       35
#define Y8_GPIO       34
#define Y7_GPIO       39
#define Y6_GPIO       36
#define Y5_GPIO       21
#define Y4_GPIO       19
#define Y3_GPIO       18
#define Y2_GPIO       5
#define VSYNC_GPIO    25
#define HREF_GPIO     23
#define PCLK_GPIO     22

WebServer server(80);

// 🔹 Start Camera Stream
void startCameraServer();

void setup() {
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO;
    config.pin_d1 = Y3_GPIO;
    config.pin_d2 = Y4_GPIO;
    config.pin_d3 = Y5_GPIO;
    config.pin_d4 = Y6_GPIO;
    config.pin_d5 = Y7_GPIO;
    config.pin_d6 = Y8_GPIO;
    config.pin_d7 = Y9_GPIO;
    config.pin_xclk = XCLK_GPIO;
    config.pin_pclk = PCLK_GPIO;
    config.pin_vsync = VSYNC_GPIO;
    config.pin_href = HREF_GPIO;
    config.pin_sscb_sda = SIOD_GPIO;
    config.pin_sscb_scl = SIOC_GPIO;
    config.pin_pwdn = PWDN_GPIO;
    config.pin_reset = RESET_GPIO;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    // Low resolution for better speed
    if(psramFound()){
      config.frame_size = FRAMESIZE_QVGA;
      config.jpeg_quality = 12;
      config.fb_count = 2;
    } else {
      config.frame_size = FRAMESIZE_QQVGA;
      config.jpeg_quality = 12;
      config.fb_count = 1;
    }

    // 🔹 Initialize Camera
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed! Error: 0x%x", err);
        return;
    }

    // 🔹 Connect to WiFi
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) { delay(1000); Serial.print("."); }

    Serial.println("\nConnected to WiFi!");
    Serial.println("ESP32-CAM IP Address: " + WiFi.localIP().toString());

    // 🔹 Start Camera Web Server
    startCameraServer();
}

void loop() {
    server.handleClient();
}
