#include <Arduino.h>
#include "LIS3DHTR.h"
#include <Wire.h>
#include <RTClib.h>  // Include RTClib for DS3231

#define WIRE Wire

LIS3DHTR<TwoWire> LIS; // I2C for accelerometer
RTC_DS3231 rtc;  // Create an RTC_DS3231 object

const int buttonPin = 6;
int mode = 0;
int steps = 0;
int prev_x = 0;
float _avg_calorie = 0.04;
float avg_step_distance_meter = 0.70104;
bool aboveThreshold = false;
bool buttonPressed = false;
bool buttonStateChanged = false;
int previousMode = -1;  // Variable to store the previous mode, initially set to an impossible mode

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  LIS.begin(WIRE, LIS3DHTR_ADDRESS_UPDATED); // I2C init for accelerometer
  delay(100);
  LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
  pinMode(buttonPin, INPUT);

  steps = 0;

  /*
  if (!rtc.begin()) {  // Initialize the RTC
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {  // If RTC lost power, set the time to compile time
    Serial.println("RTC lost power, setting time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  */

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

// Function to update steps
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

// Function to get current date and time from DS3231
String getDate() {
  DateTime now = rtc.now();
  String getDateStr = String(now.year()) + "/" + String(now.month()) + "/" + String(now.day()); 
  return getDateStr;
}

String getTime(){
  DateTime now = rtc.now();
  String getTimeStr = String(now.year()) + "/" + String(now.month()) + "/" + String(now.day()); 
  return getTimeStr;
}

void getWeather(){

}

void getTemp(){

}

void getPersonalTemp () {


}


void loop() {
  updateSteps(); // Update steps count


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
    delay(500); // Delay to ensure mode change is clearly visible
  }

  // Only display the message if the mode has changed
  if (mode != previousMode) {
    previousMode = mode;  // Update the previousMode to the current mode

    // Display different information based on mode
    Serial.println(); // Print a blank line for separation

    switch (mode) {
      case 0:
        // Empty display, do nothing
        break;

      case 1: {
        Serial.println("Welcome To Hexabit");
        break;
      }

      case 2:{
        Serial.println("Time:" + getTime());
        Serial.println("Date: " + getDate());
        break;
      }
      case 3: {
        float calories = getCalories(steps); // Get calories
        Serial.print("Steps: ");
        Serial.println(getSteps()); // Use getSteps() to get the step count
        Serial.print("Calorie: ");
        Serial.println(calories);
        break;
      }

      case 4: {
        float distance_km = getDistanceKm(steps);   // Get distance in km
        float distance_miles = getDistanceMiles(steps); // Get distance in miles
        Serial.println("Distance");
        Serial.print("Km: ");
        Serial.println(distance_km);
        Serial.print("Miles: ");
        Serial.println(distance_miles);
        break;
      }

      case 5: {
        Serial.println("Weather: ");

        break;
      }

      case 6:{
        Serial.println("Made By");
        Serial.println("Kpanesar88");
        Serial.println("v1.0");
        break;
    }
  }

  delay(100); // Adjust this delay for real-time responsiveness
}