/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-joystick
 */

#include <ezButton.h>

#define VRX_PIN1  36 // ESP32 pin GPIO39 (ADC3) connected to VRX pin
#define VRY_PIN1  35 // ESP32 pin GPIO36 (ADC0) connected to VRY pin
#define SW_PIN1   17 // ESP32 pin GPIO17 connected to SW  pin
#define VRX_PIN2  25 // ESP32 pin GPIO39 (ADC3) connected to VRX pin
#define VRY_PIN2  26 // ESP32 pin GPIO36 (ADC0) connected to VRY pin
#define SW_PIN2   3  // ESP32 pin GPIO17 connected to SW  pin

ezButton button1(SW_PIN1);
ezButton button2(SW_PIN2);

int valueX1 = 0; // to store the X-axis value
int valueY1 = 0; // to store the Y-axis value
int bValue1 = 0; // To store value of the button
int valueX2 = 0; // to store the X-axis value
int valueY2 = 0; // to store the Y-axis value
int bValue2 = 0; // To store value of the button

void setup() {
  Serial.begin(115200);

}

void loop() {
  button1.loop(); // MUST call the loop() function first
  button2.loop(); // MUST call the loop() function first

  // read X and Y analog values
  valueX1 = analogRead(VRX_PIN1);
  valueY1 = analogRead(VRY_PIN1);

  // Read the button value
  bValue1 = button1.getState();
  bValue2 = button2.getState();

  if (button1.isPressed()) {
    Serial.println("The button 1 is pressed");
    // TODO do something here
  }

  if (button1.isReleased()) {
    Serial.println("The button 1 is released");
    // TODO do something here
  }

  // read X and Y analog values
  valueX2 = analogRead(VRX_PIN2);
  valueY2 = analogRead(VRY_PIN2);

  if (button2.isPressed()) {
    Serial.println("The button 2 is pressed");
    // TODO do something here
  }

  if (button2.isReleased()) {
    Serial.println("The button 2 is released");
    // TODO do something here
  }

  // print data to Serial Monitor on Arduino IDE
  Serial.print("x1 = ");
  Serial.print(valueX1);
  Serial.print(", y1 = ");
  Serial.print(valueY1);
  Serial.print(" : button1 = ");
  Serial.print(bValue1);
  Serial.print(", x2 = ");
  Serial.print(valueX2);
  Serial.print(", y2 = ");
  Serial.print(valueY2);
  Serial.print(" : button2 = ");
  Serial.println(bValue2);
}
