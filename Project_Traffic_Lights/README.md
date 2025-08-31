# Traffic Light Control System 🚦

## Project Overview
This project simulates a **4-way traffic light intersection** using an **Arduino Uno**.  
It supports two modes:
- **Automatic mode**: Simulates normal traffic flow (Green → Yellow → Red).
- **Manual mode**: Allows the user to control the intersections using push buttons.  
  A blue LED indicates the current mode (Automatic/Manual).

## Components Used
- Arduino Uno
- Breadboard
- Jumper wires
- LEDs (Red, Yellow, Green, Blue)
- Push buttons (x2)

## Features
- Automatic and manual operation modes.
- Yellow LED lights up for 1 second during switching.
- Blue LED indicates the system mode.
- 4 intersections synchronized.

## Algorithm
1. Initialize counters, LED pins, and button states.  
2. Attach interrupts for push buttons (manual control).  
3. Automatic mode: Run standard traffic light sequence with delays.  
4. Manual mode: Wait for user input to change the light.  
5. Repeat loop for all 4 intersections.

## Code
The main source code is inside `src/traffic_light.ino`.

```cpp
// Example snippet
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  // Define LED pins and attach interrupts...
}
void loop() {
  // Call traffic light sequence function for each intersection
}
```

## How to Run
1. Open `src/traffic_light.ino` in Arduino IDE.  
2. Connect Arduino Uno to your computer.  
3. Select the correct COM port and board type.  
4. Upload the sketch.  
5. Test the system using LEDs and push buttons on a breadboard.

## Documentation
The detailed **project report** is in [`docs/Project1_Traffic_Lights.pdf`](docs/Project1_Traffic_Lights.pdf).

## License
This project is licensed under the MIT License.

