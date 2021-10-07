#include <WiFi.h>
#include "esp_camera.h"
#include "ESPAsyncWebServer.h"

#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

const boolean internet = false;
int laserPin = 3;
int ser = 1;

// 192.168.4.1

const char *AP_ssid = "I-SEE-YOU"; 
const char *AP_password = "yeetyeet";

const char *WF_ssid = "supertrouble2"; 
const char *WF_password = "trouble2008";

void startCameraServer();


void setup() {

  // Enables Serial Commmunication with ESP32
  if(ser == 1)
    Serial.begin(115200);

  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, LOW);

  if(!internet)
  {
    WiFi.mode(WIFI_AP);           
    
    WiFi.softAP(AP_ssid, AP_password);
    
    if(ser == 1) {
      Serial.print("Access Point IP address: ");
      Serial.println(WiFi.softAPIP());
    }
    
  }
  else
  {
    //WiFi.mode(WIFI_STA);

    WiFi.begin(WF_ssid, WF_password);
    while (WiFi.status() != WL_CONNECTED) 
    { 
      delay(200);
      if(ser == 1)
        Serial.print(".");
    }
    if(ser == 1) {
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());  
    }
  }

  // Camera Config, setting pins stored to variables stored in Camera_pins.h

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
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  config.frame_size = FRAMESIZE_XGA;
  config.jpeg_quality = 10;
  config.fb_count = 2;

  // Camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK)
  {
    if(ser == 1)
      Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
  /*
  server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hello World!");
    if(ser == 1)
      Serial.println("HELLO!!!!!");
 });
 server.on("/laser/off", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "ok");
    digitalWrite(laserPin, LOW);
 });
 server.on("/laser/on", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "ok");
    digitalWrite(laserPin, HIGH);
 });
 server.on("/laser", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(digitalRead(laserPin)));
 });*/

   //server.begin();
   startCameraServer();
}

void loop() {

}
