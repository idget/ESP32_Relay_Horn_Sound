/*
 * Simple Relay Test Program
 * This will turn the relay ON for 2 seconds, OFF for 2 seconds, repeatedly
 * Use this to verify your relay is working before running the main program
 */

#include <Arduino.h>

const int RELAY_PIN = 5;

void setup() {
  Serial.begin(115200);
  Serial.println("Relay Test Starting...");
  
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);  // Start with relay OFF
  
  Serial.println("Relay should be OFF now");
  delay(2000);
}

void loop() {
  // Turn relay ON
  digitalWrite(RELAY_PIN, LOW);
  Serial.println("Relay ON - Check if left terminal has 12V now!");
  delay(2000);
  
  // Turn relay OFF  
  digitalWrite(RELAY_PIN, HIGH);
  Serial.println("Relay OFF - Left terminal should be 0V now");
  delay(2000);
}