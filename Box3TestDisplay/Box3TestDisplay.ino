// ESP32-S3-BOX-3 ILI9341 LCD + GT911 Touch Example
// Gebruikt TFT_eSPI library

// Definieer de pins voor TFT_eSPI (pas aan als nodig)
#define USER_SETUP_ID 70
#define ILI9341_DRIVER

// LCD Pins
#define TFT_CS   5
#define TFT_DC   6
#define TFT_RST  7
#define TFT_MOSI 11
#define TFT_MISO 13
#define TFT_SCLK 12
#define TFT_BL   47  // Backlight

// Touch Pins (GT911)
#define TOUCH_CS 14
#define TOUCH_IRQ 35



#include <SPI.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();  // Initialiseer TFT_eSPI

void setup() {
  Serial.begin(115200);

  // Initialiseer LCD
  tft.init();
  tft.setRotation(1);  // Pas rotatie aan naar wens (0-3)
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);

  // Toon welkomstekst
  tft.drawString("ESP32-S3-BOX-3", 20, 20);
  tft.drawString("ILI9341 LCD Test", 20, 50);
  tft.drawString("Touch the screen", 20, 80);

  // Zet backlight aan
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  // Initialiseer touch (als je GT911 gebruikt)
  // Let op: TFT_eSPI ondersteunt GT911 niet standaard.
  // Voor touch kun je de XPT2046_Touch library gebruiken of een andere GT911 library.
  // Hier een eenvoudige voorbeeld voor touch detectie (zonder library):
  pinMode(TOUCH_CS, OUTPUT);
  digitalWrite(TOUCH_CS, HIGH);
  pinMode(TOUCH_IRQ, INPUT_PULLUP);

  Serial.println("Setup klaar!");
}

void loop() {
  // Lees touch (eenvoudige IRQ check)
  if (digitalRead(TOUCH_IRQ) == LOW) {
    tft.fillScreen(TFT_BLACK);
    tft.drawString("Touch detected!", 20, 110);
    delay(500);
    tft.fillScreen(TFT_BLACK);
    tft.drawString("ESP32-S3-BOX-3", 20, 20);
    tft.drawString("ILI9341 LCD Test", 20, 50);
    tft.drawString("Touch the screen", 20, 80);
  }
  delay(10);
}