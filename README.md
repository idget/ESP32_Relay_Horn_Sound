# ESP32_Relay_Horn_Sound
Make a DJ Horn sound with a car horn using ESP32 and relay control

## Overview
This project uses an ESP32 microcontroller to control a relay that drives a 12V car horn, producing the famous DJ horn sound pattern. The classic pattern consists of three quick honks with specific timing.

## Features
- **DJ Horn Pattern**: Three quick honks (150ms each) with short pauses
- **Button Control**: Manual trigger using ESP32's built-in boot button (GPIO 0)
- **Safety**: Proper relay control with debounced button input
- **Serial Monitoring**: Debug output for monitoring system status
- **Customizable**: Easy to modify timing and patterns

## Hardware Requirements
- ESP32 development board (any variant)
- Relay module (5V input, capable of switching 12V/high current)
- 12V car horn
- 12V power supply (sufficient current for your horn)
- Jumper wires
- Breadboard or PCB for connections
- Optional: External push button and resistor

## Circuit Diagram
```
ESP32                    Relay Module              12V Car Horn
-----                    ------------              ------------
GPIO 2  ────────────────► IN                      
                         VCC ◄──── 5V (or 3.3V)   
GND     ────────────────► GND                      
                         COM ◄──────────────────── Horn Terminal 1
                         NO  ◄──── 12V Power +     
                                                   
12V Power Supply                                   Horn Terminal 2
----------------                                   ├─────────────
+12V ──┬─────────────────► Relay NO               │
       └─────────────────────────────────────────┘
GND  ──┬─────────────────► Common Ground          
       └─────────────────► ESP32 GND              

Button (Optional)
-----------------
GPIO 0  ◄──┬──── Button ──── GND
           │
           └──── 10kΩ ──── 3.3V (pull-up)
```

## Pin Configuration
| Component | ESP32 Pin | Description |
|-----------|-----------|-------------|
| Relay IN  | GPIO 2    | Controls relay activation |
| Button    | GPIO 0    | Manual trigger (built-in boot button) |
| Power     | 5V/3.3V   | Power for relay module VCC |
| Ground    | GND       | Common ground connection |

## Installation & Usage

### 1. Arduino IDE Setup
1. Install the ESP32 board package in Arduino IDE
2. Select your ESP32 board (e.g., "ESP32 Dev Module")
3. Choose the correct COM port

### 2. Upload Code
1. Download or copy the `ESP32_Relay_Horn_Sound.ino` file
2. Open it in Arduino IDE
3. Upload to your ESP32

### 3. Hardware Connections
1. Connect the relay module IN pin to ESP32 GPIO 2
2. Connect relay VCC to ESP32 5V (or 3.3V depending on relay module)
3. Connect relay GND to ESP32 GND
4. Connect car horn between relay COM and NO terminals
5. Connect 12V power supply to complete the horn circuit

### 4. Operation
1. Open Serial Monitor (115200 baud) to see debug output
2. Press the ESP32 boot button (GPIO 0) to trigger the DJ horn sound
3. The system will play three quick honks with proper timing
4. Wait for the completion message before triggering again

## Code Structure
- **`setup()`**: Initializes pins and serial communication
- **`loop()`**: Monitors button press and triggers horn pattern
- **`isButtonPressed()`**: Debounced button reading
- **`playDJHornSound()`**: Executes the classic DJ horn pattern
- **`playCustomPattern()`**: Optional function for custom patterns

## Customization

### Timing Adjustments
Modify these constants in the code:
```cpp
const int HONK_DURATION = 150;  // Duration of each honk (ms)
const int SHORT_PAUSE = 100;    // Pause between honks (ms)
const int LONG_PAUSE = 800;     // Pause before next trigger (ms)
```

### Different Patterns
Use the `playCustomPattern()` function to create your own horn patterns:
```cpp
int durations[] = {200, 300, 150};  // Honk durations
int pauses[] = {100, 200};          // Pauses between honks
playCustomPattern(durations, pauses, 3);
```

## Safety Considerations
⚠️ **Important Safety Notes:**
- Ensure your relay can handle the current draw of your car horn
- Use appropriate fusing for the 12V circuit
- Double-check all connections before powering on
- Car horns can be very loud - consider hearing protection
- Ensure proper ventilation if using indoors
- Be mindful of noise ordinances and neighbor considerations

## Troubleshooting

### Horn Doesn't Sound
- Check 12V power supply connections
- Verify relay is clicking when triggered
- Test horn directly with 12V supply
- Check relay current rating vs horn requirements

### No Response to Button Press
- Verify GPIO 0 connection
- Check serial monitor for debug messages
- Ensure button is properly debounced
- Try external button with pull-up resistor

### Relay Not Clicking
- Check ESP32 to relay IN pin connection
- Verify relay VCC voltage (5V or 3.3V)
- Test with LED on GPIO 2 to confirm output

## License
MIT License - See LICENSE file for details

## Contributing
Feel free to submit issues, fork the repository, and create pull requests for any improvements.
