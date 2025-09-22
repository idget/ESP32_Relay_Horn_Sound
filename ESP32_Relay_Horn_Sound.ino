/*
 * ESP32 Relay Horn Sound - DJ Horn Pattern
 * 
 * This sketch controls a relay to drive a 12V car horn
 * and produce the famous DJ horn sound pattern.
 * 
 * Hardware Requirements:
 * - ESP32 development board
 * - Relay module (capable of handling 12V car horn current)
 * - 12V car horn
 * - 12V power supply for the horn
 * - Push button (optional, for manual trigger)
 * 
 * Wiring:
 * - ESP32 GPIO 2 -> Relay IN pin
 * - ESP32 GPIO 0 -> Push button (with pull-up resistor)
 * - Relay COM -> One terminal of car horn
 * - Relay NO -> 12V power supply positive
 * - Car horn other terminal -> 12V power supply negative/ground
 * - ESP32 GND -> Common ground with relay and button
 * 
 * Author: ESP32_Relay_Horn_Sound
 * License: MIT
 */

// Pin definitions
const int RELAY_PIN = 2;        // GPIO pin connected to relay
const int BUTTON_PIN = 0;       // GPIO pin connected to push button (boot button on most ESP32 boards)

// DJ Horn sound timing (in milliseconds)
const int HONK_DURATION = 150;  // Duration of each honk
const int SHORT_PAUSE = 100;    // Short pause between honks in the pattern
const int LONG_PAUSE = 800;     // Long pause before repeating pattern

// Variables for button handling
bool lastButtonState = HIGH;
bool buttonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);
  Serial.println("ESP32 DJ Horn Sound Controller");
  Serial.println("==============================");
  
  // Initialize pins
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Ensure relay is off initially
  digitalWrite(RELAY_PIN, LOW);
  
  Serial.println("System initialized. Press button to trigger DJ horn sound.");
  Serial.println("Pin Configuration:");
  Serial.printf("Relay Pin: GPIO %d\n", RELAY_PIN);
  Serial.printf("Button Pin: GPIO %d\n", BUTTON_PIN);
}

void loop() {
  // Check for button press
  if (isButtonPressed()) {
    Serial.println("Button pressed! Playing DJ horn sound...");
    playDJHornSound();
    delay(1000); // Prevent multiple triggers
  }
  
  // Small delay to prevent excessive CPU usage
  delay(10);
}

bool isButtonPressed() {
  // Read the button state
  int reading = digitalRead(BUTTON_PIN);
  
  // Check if button state has changed
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  // If enough time has passed since last state change
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If button state has actually changed
    if (reading != buttonState) {
      buttonState = reading;
      
      // Return true only when button is pressed (LOW due to pull-up)
      if (buttonState == LOW) {
        lastButtonState = reading;
        return true;
      }
    }
  }
  
  lastButtonState = reading;
  return false;
}

void playDJHornSound() {
  Serial.println("Starting DJ horn pattern...");
  
  // Classic DJ horn pattern: 3 quick honks
  for (int i = 0; i < 3; i++) {
    Serial.printf("Honk %d/3\n", i + 1);
    
    // Turn on horn (activate relay)
    digitalWrite(RELAY_PIN, HIGH);
    delay(HONK_DURATION);
    
    // Turn off horn (deactivate relay)
    digitalWrite(RELAY_PIN, LOW);
    
    // Short pause between honks (except after the last one)
    if (i < 2) {
      delay(SHORT_PAUSE);
    }
  }
  
  Serial.println("DJ horn pattern complete!");
  
  // Long pause before allowing another trigger
  delay(LONG_PAUSE);
}

void activateHorn() {
  digitalWrite(RELAY_PIN, HIGH);
}

void deactivateHorn() {
  digitalWrite(RELAY_PIN, LOW);
}

// Optional: Function to play a custom horn pattern
void playCustomPattern(int* durations, int* pauses, int count) {
  for (int i = 0; i < count; i++) {
    activateHorn();
    delay(durations[i]);
    deactivateHorn();
    
    if (i < count - 1) {
      delay(pauses[i]);
    }
  }
}