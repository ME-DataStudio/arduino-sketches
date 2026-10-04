#include <GxEPD2.h>
#include <GxEPD2_4C.h>
#include <GxEPD2_EPD.h>
#include <GxEPD2_GFX.h>

//Unexpected maker series D lib
#include <UMSeriesD.h>
UMSeriesD umseriesd;

#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <time.h>

// Network and API Configuration
const int MAX_NETWORKS = 1;
const char* ssid[MAX_NETWORKS] = {"ORBI71"};
const char* password[MAX_NETWORKS] = {"Cnstf@0305"};
//const char* apiKey = "087fb5007eb9ba4761dd0e9901c59249";
//const float latitude = 53.174145180943;  // for Ohrid
//const float longitude = 6.6305010088279; // for Ohrid
int currentDayIndex = 0;
int lastUpdateHour = -1;

// epaper Definitions
#define BUSY 12
#define RST 14
#define DC 6
#define CS 5
#define CLK 17
#define MOSI 18


// Global Variables
RTC_DATA_ATTR bool rtcInvertDisplay = false;  // Persists across deep sleep
bool invertDisplay = false;  // Current display state

// Display Configuration
GxEPD2_4C < GxEPD2_437c, GxEPD2_437c::HEIGHT / 2 > epd(GxEPD2_437c(/*CS=D8*/ CS, /*DC=D3*/ DC, /*RST=D4*/ RST, /*BUSY=D2*/ BUSY)); // Waveshare 4.37" 4-color

//**************************************
// Helper functions
//**************************************
bool connectToWiFi() {
  for (int i = 0; i < MAX_NETWORKS; i++) {
    Serial.printf("Trying WiFi %d/%d: %s\n", i+1, MAX_NETWORKS, ssid[i]);
    WiFi.begin(ssid[i], password[i]);
    
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
      delay(250);
      Serial.print(".");
    }
    
    if (WiFi.status() == WL_CONNECTED) {
      Serial.printf("\nConnected to %s\n", ssid[i]);
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());
      return true;
    }
    Serial.println("\nConnection failed");
    WiFi.disconnect();
    delay(1000);
  }
  return false;
}

void epdInit() {
  epd.init(115200, true, 50, false);
  epd.setRotation(0);
  epd.setTextColor(invertDisplay ? GxEPD_WHITE : GxEPD_BLACK);
  epd.setFont(&FreeMonoBold9pt7b);
  epd.setFullWindow();
  Serial.println("E-paper initialized");
}




void fetchCurrentImage() {
  String imageURL;
  WiFiClient client;
  HTTPClient http;
  String url = "http://192.168.1.6:4567/api/display";
  
  http.begin(client, url);
  http.addHeader("id", "10:CF:0F:BB:9C:89");
  http.addHeader("Content-Type","application/json");
  http.addHeader("access-token","22gSZSgoQTwld14G9lsH");
  int httpCode = http.GET();
  Serial.println("getting image from TRMNL server.");
  Serial.println(httpCode);
  if (httpCode == 200) {
    String payload = http.getString();
    Serial.println(payload);
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, payload);
    
    if (!error) {
      imageURL = doc["image_url"].as<String>();

      //return imageURL;
    }
  }
  http.end();
  //return "no url found";
}

void setup() {
  Serial.begin(115200);
  delay(2000);
 
  Serial.println("437in4C Display Booting...");

  epdInit();
  delay(5000);
  Serial.println("Clear display!");
  epd.fillScreen(invertDisplay ? GxEPD_BLACK : GxEPD_WHITE);
  epd.display();
  // Attempt WiFi connection
  bool wifiConnected = connectToWiFi();

  if (!wifiConnected) {
    Serial.println("Failed to connect to any network");
    
    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) {
      lastUpdateHour = timeinfo.tm_hour;
    } else {
      lastUpdateHour = 0;
    }
  } else {
    //syncTime();
    Serial.println("<SETUP>Getting image url ...");
    fetchCurrentImage();    

  }

   epd.hibernate();
 
  //Serial.println("Entering deep sleep...");
  // esp_sleep_enable_ext0_wakeup(GPIO_NUM_2, 0); // Wake on button press
  //esp_sleep_enable_timer_wakeup(900LL * 1000000); // 15 min
  //esp_deep_sleep_start();
}

void loop() {
  // Empty - device will be in deep sleep
} 