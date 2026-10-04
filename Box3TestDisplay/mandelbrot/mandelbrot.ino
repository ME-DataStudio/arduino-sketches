#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void initDisplay()
{
    // BOX-3 LCD reset
    pinMode(48, OUTPUT);
    digitalWrite(48, HIGH);
    delay(100);
    digitalWrite(48, LOW);
    delay(100);

    tft.init();
    tft.setRotation(3);

    tft.fillScreen(TFT_BLACK);

    tft.setTextDatum(TL_DATUM);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);

    tft.drawString("BRESSER WEATHER", 10, 10);
}

void displayWeather(float temperature, float humidity)
{
    // Clear the value areas
    tft.fillRect(10, 55, 300, 55, TFT_BLACK);
    tft.fillRect(10, 125, 300, 55, TFT_BLACK);

    tft.setTextSize(3);

    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.drawString(
        String(temperature, 1) + " C",
        20,
        65
    );

    tft.setTextColor(TFT_CYAN, TFT_BLACK);
    tft.drawString(
        String(humidity, 0) + " %",
        20,
        135
    );
}

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println("Starting TFT...");

    tft.init();

    Serial.println("TFT initialized");

    tft.setRotation(3);

    tft.fillScreen(TFT_RED);
    delay(1000);

    tft.fillScreen(TFT_GREEN);
    delay(1000);

    tft.fillScreen(TFT_BLUE);
    delay(1000);

    tft.fillScreen(TFT_BLACK);

    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(3);
    tft.setCursor(10, 10);

    tft.println("ESP32-S3 BOX");
    tft.println("TFT OK");
}

void loop()
{
}