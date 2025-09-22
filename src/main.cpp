/*
 * ESP32 DJ Car Horn Sound Controller
 * 
 * This program creates the famous DJ car horn sound pattern using a relay
 * to control a 12V car horn. The pattern mimics the classic 
 * "beep beep beep, beeeeeep" DJ sound.
 * 
 * Hardware connections:
 * - GPIO 4: Momentary button (with internal pull-up)
 * - GPIO 5: Relay control (drives relay IN1 pin)
 * - 3.3V and GND: Power for relay logic side
 * - Relay output: Controls 12V car horn
 * 
 * Author: ESP32 DJ Horn Project
 * License: MIT
 */

#include <Arduino.h>

// Function declarations
void checkButton();
void startHornPattern();
void handleHornPattern();
void activateHorn();
void deactivateHorn();
void endHornPattern();

// Pin definitions
const int BUTTON_PIN = 4;    // Momentary button input
const int RELAY_PIN = 5;     // Relay control output

// Button debouncing variables
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int lastButtonState = HIGH;
int buttonState = HIGH;
bool lastButtonReading = HIGH;

// Horn pattern timing (in milliseconds)
const int SHORT_BEEP = 150;     // Duration of short beeps
const int LONG_BEEP = 800;      // Duration of long beep
const int BEEP_PAUSE = 100;     // Pause between beeps
const int PATTERN_PAUSE = 200;  // Pause before long beep
const int COOLDOWN = 1000;      // Cooldown after full pattern

// Horn pattern state
bool hornActive = false;
unsigned long patternStartTime = 0;
int currentBeep = 0;
bool inCooldown = false;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);
  Serial.println("ESP32 DJ Car Horn Initialized");
  
  // Configure pins
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Enable internal pull-up resistor
  pinMode(RELAY_PIN, OUTPUT);
  
  // Ensure relay is off initially (HIGH keeps relay off)
  digitalWrite(RELAY_PIN, HIGH);
  
  Serial.println("Ready! Press button to activate DJ horn sound.");
}

void loop() {
  // Read button with debouncing
  checkButton();
  
  // Handle horn pattern if active
  if (hornActive) {
    handleHornPattern();
  }
}

void checkButton() {
  // Read the button state
  bool reading = digitalRead(BUTTON_PIN);
  
  // Check if button state has changed (for debouncing)
  if (reading != lastButtonReading) {
    lastDebounceTime = millis();
  }
  
  // If enough time has passed, consider the reading stable
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If button state has actually changed
    if (reading != buttonState) {
      buttonState = reading;
      
      // If button is pressed (LOW due to pull-up) and horn is not active
      if (buttonState == LOW && !hornActive && !inCooldown) {
        startHornPattern();
      }
    }
  }
  
  lastButtonReading = reading;
}

void startHornPattern() {
  Serial.println("Starting DJ horn pattern!");
  hornActive = true;
  patternStartTime = millis();
  currentBeep = 0;
  activateHorn();
}

void handleHornPattern() {
  unsigned long elapsed = millis() - patternStartTime;
  
  switch (currentBeep) {
    case 0: // First short beep
      if (elapsed >= SHORT_BEEP) {
        deactivateHorn();
        patternStartTime = millis();
        currentBeep++;
      }
      break;
      
    case 1: // Pause after first beep
      if (elapsed >= BEEP_PAUSE) {
        activateHorn();
        patternStartTime = millis();
        currentBeep++;
      }
      break;
      
    case 2: // Second short beep
      if (elapsed >= SHORT_BEEP) {
        deactivateHorn();
        patternStartTime = millis();
        currentBeep++;
      }
      break;
      
    case 3: // Pause after second beep
      if (elapsed >= BEEP_PAUSE) {
        activateHorn();
        patternStartTime = millis();
        currentBeep++;
      }
      break;
      
    case 4: // Third short beep
      if (elapsed >= SHORT_BEEP) {
        deactivateHorn();
        patternStartTime = millis();
        currentBeep++;
      }
      break;
      
    case 5: // Pause before long beep
      if (elapsed >= PATTERN_PAUSE) {
        activateHorn();
        patternStartTime = millis();
        currentBeep++;
      }
      break;
      
    case 6: // Long beep
      if (elapsed >= LONG_BEEP) {
        deactivateHorn();
        endHornPattern();
      }
      break;
  }
}

void activateHorn() {
  digitalWrite(RELAY_PIN, LOW);   // Activate relay (LOW triggers most relay modules)
  Serial.println("Horn ON - GPIO5 LOW - Relay should switch to NO");
  Serial.print("GPIO5 state: ");
  Serial.println(digitalRead(RELAY_PIN));
}

void deactivateHorn() {
  digitalWrite(RELAY_PIN, HIGH);  // Deactivate relay (HIGH releases relay)
  Serial.println("Horn OFF - GPIO5 HIGH - Relay back to NC");
  Serial.print("GPIO5 state: ");
  Serial.println(digitalRead(RELAY_PIN));
}

void endHornPattern() {
  Serial.println("DJ horn pattern complete!");
  hornActive = false;
  inCooldown = true;
  
  // Start cooldown timer to prevent rapid triggering
  delay(COOLDOWN);
  inCooldown = false;
  Serial.println("Ready for next activation.");
}