#include <Arduino.h>
#include "LIS3DHTR.h"
#include <Wire.h>
#include <U8g2lib.h>

#define WIRE Wire

LIS3DHTR<TwoWire> LIS; // I2C for accelerometer
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE); // Initialize OLED using U8g2 library

const int buttonPin = 6;
int mode = 0;
int steps = 0;
int prev_x = 0;
float _avg_calorie = 0.04;
float avg_step_distance_meter = 0.70104;
bool aboveThreshold = false;
bool buttonPressed = false;
bool buttonStateChanged = false;

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  LIS.begin(WIRE, LIS3DHTR_ADDRESS_UPDATED); // I2C init for accelerometer
  delay(100);
  LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
  pinMode(buttonPin, INPUT);

  steps = 0;

  // Initialize the OLED display
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.clearBuffer();                  // Clear internal memory
  u8g2.drawStr(0, 10, "Initializing"); // Display initializing message
  u8g2.sendBuffer();                   // Transfer internal memory to the display

  delay(2000); // Wait for 2 seconds to show initializing message
}

// Function to calculate calories
float getCalories(int steps) {
  return steps * _avg_calorie;
}

// Function to calculate distance in kilometers
float getDistanceKm(int steps) {
  return (steps * avg_step_distance_meter) / 1000;
}

// Function to calculate distance in miles
float getDistanceMiles(int steps) {
  return (steps * avg_step_distance_meter) / 1609;
}

// Function to get the current step count
int getSteps() {
  return steps;
}

void updateSteps() {
  float current_x = LIS.getAccelerationX();
  if (!aboveThreshold && ((prev_x <= 0.5 && current_x > 0.5) || (prev_x >= -0.5 && current_x < -0.5))) {
    steps++;
    aboveThreshold = true;
  } else if (aboveThreshold && (current_x <= 0.5 && current_x >= -0.5)) {
    aboveThreshold = false;
  }
  prev_x = current_x;
}

void loop() {
  updateSteps(); // Update steps count
 
  Serial.print("Steps: ");
  Serial.println(steps);

  bool currentButtonState = digitalRead(buttonPin) == LOW;
  if (currentButtonState != buttonPressed) {
    buttonStateChanged = true;
    buttonPressed = currentButtonState;
  } else {
    buttonStateChanged = false;
  }

  if (buttonStateChanged && buttonPressed) {
    mode = (mode + 1) % 5;
    Serial.print("Mode changed to: ");
    Serial.println(mode);
    delay(500);
  }

  // Display different information based on mode
  u8g2.clearBuffer(); // Clear internal buffer

  switch (mode) {
    case 0:
      // Empty display, do nothing
      break;

    case 1:
      u8g2.setCursor(0, 10);
      u8g2.print("Welcome To");
      u8g2.setCursor(0, 20);
      u8g2.print("Hexabit");
      break;

    case 2:
      {
        float calories = getCalories(steps); // Get calories
        u8g2.setCursor(0, 10);
        u8g2.print("Steps: ");
        u8g2.print(getSteps()); // Use getSteps() to get the step count
        u8g2.setCursor(0, 20);
        u8g2.print("Calorie: ");
        u8g2.print(calories);
      }
      break;

    case 3:
      {
        float distance_km = getDistanceKm(steps);   // Get distance in km
        float distance_miles = getDistanceMiles(steps); // Get distance in miles
        u8g2.setCursor(0, 10);
        u8g2.print("Distance");
        u8g2.setCursor(0, 20);
        u8g2.print("Km: ");
        u8g2.print(distance_km);
        u8g2.setCursor(0, 30);
        u8g2.print("Miles: ");
        u8g2.print(distance_miles);
      }
      break;

    case 4:
      u8g2.setCursor(0, 10);
      u8g2.print("Made By");
      u8g2.setCursor(0, 20);
      u8g2.print("Kpanesar88");
      u8g2.setCursor(0, 30);
      u8g2.print("v1.0");
      break;
  }

  u8g2.sendBuffer(); // Transfer internal memory to the display
  delay(100); // Adjust this delay for real-time responsiveness
}
