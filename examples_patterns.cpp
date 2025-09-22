/*
 * Custom Horn Patterns Examples
 * 
 * This file contains examples of different horn patterns you can use
 * with the ESP32_Relay_Horn_Sound project.
 * 
 * Copy and paste these into your main sketch to try different sounds.
 */

// Example 1: Classic DJ Horn (already implemented in main sketch)
void playClassicDJHorn() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(RELAY_PIN, HIGH);
    delay(150);
    digitalWrite(RELAY_PIN, LOW);
    if (i < 2) delay(100);
  }
}

// Example 2: Ship Horn Pattern
void playShipHorn() {
  digitalWrite(RELAY_PIN, HIGH);
  delay(1000);  // Long honk
  digitalWrite(RELAY_PIN, LOW);
  delay(200);
  
  digitalWrite(RELAY_PIN, HIGH);
  delay(500);   // Medium honk
  digitalWrite(RELAY_PIN, LOW);
  delay(200);
  
  digitalWrite(RELAY_PIN, HIGH);
  delay(1000);  // Long honk
  digitalWrite(RELAY_PIN, LOW);
}

// Example 3: Car Alarm Pattern
void playCarAlarm() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(RELAY_PIN, HIGH);
    delay(80);   // Very short honks
    digitalWrite(RELAY_PIN, LOW);
    delay(80);
  }
}

// Example 4: Morse Code SOS
void playSOSPattern() {
  // S (dot dot dot)
  for (int i = 0; i < 3; i++) {
    digitalWrite(RELAY_PIN, HIGH);
    delay(100);
    digitalWrite(RELAY_PIN, LOW);
    delay(100);
  }
  delay(200);
  
  // O (dash dash dash)
  for (int i = 0; i < 3; i++) {
    digitalWrite(RELAY_PIN, HIGH);
    delay(300);
    digitalWrite(RELAY_PIN, LOW);
    delay(100);
  }
  delay(200);
  
  // S (dot dot dot)
  for (int i = 0; i < 3; i++) {
    digitalWrite(RELAY_PIN, HIGH);
    delay(100);
    digitalWrite(RELAY_PIN, LOW);
    delay(100);
  }
}

// Example 5: Mexican Hat Dance Pattern
void playMexicanHatDance() {
  int pattern[] = {200, 200, 300, 200, 200, 500};
  int pauses[] = {150, 150, 100, 150, 150};
  
  for (int i = 0; i < 6; i++) {
    digitalWrite(RELAY_PIN, HIGH);
    delay(pattern[i]);
    digitalWrite(RELAY_PIN, LOW);
    if (i < 5) delay(pauses[i]);
  }
}

// Example 6: Using the playCustomPattern function from main sketch
void setupCustomPatterns() {
  // Pattern 1: Ascending honks
  int ascending[] = {100, 150, 200, 250, 300};
  int ascending_pauses[] = {50, 50, 50, 50};
  // playCustomPattern(ascending, ascending_pauses, 5);
  
  // Pattern 2: Quick beeps
  int beeps[] = {50, 50, 50, 50, 50, 50};
  int beep_pauses[] = {30, 30, 30, 30, 30};
  // playCustomPattern(beeps, beep_pauses, 6);
  
  // Pattern 3: Two-tone pattern
  int two_tone[] = {300, 200, 300, 200};
  int two_tone_pauses[] = {100, 150, 100};
  // playCustomPattern(two_tone, two_tone_pauses, 4);
}

/*
 * To use any of these patterns in your main sketch:
 * 
 * 1. Copy the function you want to your main .ino file
 * 2. Call it instead of or in addition to playDJHornSound()
 * 3. You can modify the timing values to suit your preference
 * 
 * For example, in your loop() function:
 * 
 * if (isButtonPressed()) {
 *   playShipHorn();  // Instead of playDJHornSound()
 *   delay(1000);
 * }
 */