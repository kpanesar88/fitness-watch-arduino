#include <Arduino.h>
#include "LIS3DHTR.h"
#include <Wire.h>
#include <RTClib.h>  // Include RTClib for DS3231 (Real-Time Clock)

// Define the I2C interface for communication
#define WIRE Wire

// Create LIS3DHTR object for accelerometer and RTC object for real-time clock
LIS3DHTR<TwoWire> LIS;
RTC_DS3231 rtc;

const int buttonPin = 6;  // Define the pin number for the button

// Variables to track mode, steps, and previous accelerometer readings
int mode = 0;
int steps = 0;
int prev_x = 0;

// Constants for calorie and step distance calculation
float _avg_calorie = 0.04;
float avg_step_distance_meter = 0.70104;

// Flags and state variables
bool aboveThreshold = false;  // Used to detect step threshold
bool buttonPressed = false;   // Used to detect if the button is pressed
bool buttonStateChanged = false; // Flag to track button state change
int previousMode = -1;  // Variable to store the previous mode, initially set to an impossible mode

void setup() {
  Serial.begin(9600);  // Start the serial communication at 9600 baud rate
  while (!Serial) {}  // Wait for the serial communication to be ready

  // Initialize accelerometer
  LIS.begin(WIRE, LIS3DHTR_ADDRESS_UPDATED); // I2C init for accelerometer
  delay(100);  // Short delay for initialization
  LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ); // Set accelerometer data rate to 50Hz
  pinMode(buttonPin, INPUT);  // Set the button pin as input

  steps = 0;  // Initialize step count

  // Initialize RTC (Real-Time Clock)
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");  // Error message if RTC is not detected
    while (1);  // Stop execution
  }

  // Check if RTC lost power and set the time to compile time if necessary
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting time to compile time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set RTC to the compile time
  }
}

// Function to calculate calories burned based on steps
float getCalories(int steps) {
  return steps * _avg_calorie;
}

// Function to calculate distance in kilometers based on steps
float getDistanceKm(int steps) {
  return (steps * avg_step_distance_meter) / 1000;
}

// Function to calculate distance in miles based on steps
float getDistanceMiles(int steps) {
  return (steps * avg_step_distance_meter) / 1609;
}

// Function to return the current step count
int getSteps() {
  return steps;
}

// Function to update the step count based on accelerometer readings
void updateSteps() {
  float current_x = LIS.getAccelerationX();  // Get current X-axis acceleration
  // Check for step detection based on acceleration threshold
  if (!aboveThreshold && ((prev_x <= 0.5 && current_x > 0.5) || (prev_x >= -0.5 && current_x < -0.5))) {
    steps++;  // Increment step count
    aboveThreshold = true;  // Set the threshold flag
  } else if (aboveThreshold && (current_x <= 0.5 && current_x >= -0.5)) {
    aboveThreshold = false;  // Reset the threshold flag
  }
  prev_x = current_x;  // Update previous acceleration value
}

// Helper function to add leading zeros to date/time elements (for formatting)
String formatTwoDigits(int number) {
  return (number < 10) ? "0" + String(number) : String(number);
}

// Function to get the current date in YYYY/MM/DD format
String getDate() {
  DateTime now = rtc.now();  // Get the current time from RTC
  // Format date as a string
  String getDateStr = String(now.year()) + "/" + formatTwoDigits(now.month()) + "/" + formatTwoDigits(now.day());
  return getDateStr;
}

// Function to get the current time in HH:MM format (without seconds)
String getTime() {
  DateTime now = rtc.now();  // Get the current time from RTC
  // Format time as a string
  String getTimeStr = formatTwoDigits(now.hour()) + ":" + formatTwoDigits(now.minute());
  return getTimeStr;
}

// Function to get weather data (hardcoded for testing purposes)
String getWeather() {
  // Return a static weather value for testing purposes
  return "Sunny, 25°C";
}

void loop() {
  updateSteps();  // Update the step count based on accelerometer data

  // Read the current button state and check if it has changed
  bool currentButtonState = digitalRead(buttonPin) == LOW;
  if (currentButtonState != buttonPressed) {
    buttonStateChanged = true;  // If the state has changed, set the flag
    buttonPressed = currentButtonState;
  } else {
    buttonStateChanged = false;  // No state change detected
  }

  // If the button state has changed and the button is pressed
  if (buttonStateChanged && buttonPressed) {
    mode = (mode + 1) % 6;  // Cycle through the modes
    // Serial.print("Mode changed to: ");
    // Serial.println(mode);  // Display the current mode
    delay(100);  // Delay to debounce the button press
  }

  // Only display the message if the mode has changed
  if (mode != previousMode) {
    previousMode = mode;  // Update the previous mode to the current mode

    // Display different information based on the selected mode
    Serial.println();  // Print a blank line for separation

    switch (mode) {
      case 0:
        // Empty display, do nothing
        break;

      case 1: {
        Serial.println("Welcome To Hexabit");  // Display welcome message
        break;
      }

      case 2: {
        // Display the current time and date
        Serial.println("Time: " + getTime());
        Serial.println("Date: " + getDate());
        break;
      }

      case 3: {
        // Display the current step count and calories burned
        float calories = getCalories(steps);  // Calculate calories
        Serial.print("Steps: ");
        Serial.println(getSteps());  // Display step count
        Serial.print("Calories: ");
        Serial.println(calories);  // Display calories burned
        break;
      }

      case 4: {
        // Display the distance in kilometers and miles
        float distance_km = getDistanceKm(steps);  // Calculate distance in kilometers
        float distance_miles = getDistanceMiles(steps);  // Calculate distance in miles
        Serial.println("Distance");
        Serial.print("Km: ");
        Serial.println(distance_km);  // Display distance in kilometers
        Serial.print("Miles: ");
        Serial.println(distance_miles);  // Display distance in miles
        break;
      }

      case 5: {
        // Display author information and version
        Serial.println("Made By");
        Serial.println("Kpanesar88");
        Serial.println("v1.0");
        break;
      }
    }
  }

  delay(100);  // Small delay for responsiveness
}
