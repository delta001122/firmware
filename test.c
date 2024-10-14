#include "esp_camera.h"  // Include the ESP32-CAM library

#include <WiFi.h>
 
// Camera settings (ESP32-CAM pin configuration)

#define CAMERA_MODEL_AI_THINKER // Select camera model

#include "camera_pins.h"
 
// Wi-Fi credentials (replace with your network's SSID and password)

const char* ssid = "your-SSID";

const char* password = "your-PASSWORD";
 
// Function to initialize the camera

void initCamera() {

  camera_config_t config;

  config.ledc_channel = LEDC_CHANNEL_0;

  config.ledc_timer = LEDC_TIMER_0;

  config.pin_d0 = Y2_GPIO_NUM;

  config.pin_d1 = Y3_GPIO_NUM;

  config.pin_d2 = Y4_GPIO_NUM;

  config.pin_d3 = Y5_GPIO_NUM;

  config.pin_d4 = Y6_GPIO_NUM;

  config.pin_d5 = Y7_GPIO_NUM;

  config.pin_d6 = Y8_GPIO_NUM;

  config.pin_d7 = Y9_GPIO_NUM;

  config.pin_xclk = XCLK_GPIO_NUM;

  config.pin_pclk = PCLK_GPIO_NUM;

  config.pin_vsync = VSYNC_GPIO_NUM;

  config.pin_href = HREF_GPIO_NUM;

  config.pin_sscb_sda = SIOD_GPIO_NUM;

  config.pin_sscb_scl = SIOC_GPIO_NUM;

  config.pin_pwdn = PWDN_GPIO_NUM;

  config.pin_reset = RESET_GPIO_NUM;

  config.pin_xclk = XCLK_GPIO_NUM;

  config.xclk_freq_hz = 20000000;

  config.pixel_format = PIXFORMAT_JPEG; // JPEG for streaming
 
  if(psramFound()){

    config.frame_size = FRAMESIZE_VGA; // VGA size image

    config.jpeg_quality = 10;          // Higher quality (lower value means higher quality)

    config.fb_count = 2;               // Number of frame buffers

  } else {

    config.frame_size = FRAMESIZE_QVGA; // QVGA if PSRAM is not found

    config.jpeg_quality = 12;           // Lower quality

    config.fb_count = 1;

  }
 
  // Initialize the camera

  if (!esp_camera_init(&config)) {

    Serial.println("Camera initialized");

  } else {

    Serial.println("Camera initialization failed");

    return;

  }

}
 
// Function to capture a photo and handle memory allocation

void capturePhoto() {

  // Take a picture

  camera_fb_t *fb = esp_camera_fb_get();  // Get the camera frame buffer
 
  if (!fb) {

    Serial.println("Camera capture failed");

    return;

  }
 
  // Allocate memory for the image buffer

  size_t imageSize = fb->len;  // Get the image size

  uint8_t *imageBuffer = (uint8_t*) malloc(imageSize);  // Allocate memory dynamically

  if (imageBuffer == NULL) {

    Serial.println("Memory allocation failed!");  // Check if memory allocation was successful

    esp_camera_fb_return(fb);  // Free the frame buffer

    return;

  }
 
  // Copy the image data to the allocated buffer

  memcpy(imageBuffer, fb->buf, imageSize);  // Copy the image from frame buffer to allocated memory

  esp_camera_fb_return(fb);  // Free the frame buffer

  // Example usage of the imageBuffer (e.g., send over Wi-Fi)

  Serial.println("Photo captured and stored in dynamically allocated memory.");

  // Simulate using the buffer (e.g., sending data, processing, etc.)

  // For example, you can send the imageBuffer over a Wi-Fi connection here

  // Free the dynamically allocated memory

  free(imageBuffer);  // Free the memory after usage

  Serial.println("Memory freed.");

}
 
void setup() {

  Serial.begin(115200);

  // Initialize the camera

  initCamera();
 
  // Connect to Wi-Fi

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);

    Serial.println("Connecting to WiFi...");

  }

  Serial.println("Connected to WiFi");
 
  // Capture a photo

  capturePhoto();

}
 
void loop() {

  // Capture and process more photos if necessary

  delay(10000);  // Wait 10 seconds before taking another photo

}

 
