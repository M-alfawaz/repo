/* Traffic Light Control System (4-way) – Arduino Uno
   Modes:
   - Automatic: standard sequence (Green → Yellow → Red)
   - Manual: toggle with Button on D2; advance to next intersection with Button on D3
   - Blue LED (A0) indicates Manual mode ON

   Wiring notes:
   - Buttons assumed with pull-down to GND and connected to +5V when pressed.
     If you use INPUT_PULLUP instead, flip the interrupt edge to FALLING and invert logic.
*/

// ==== Pins ====
// Status / mode LED (blue)
const int LED_MODE = A0;        // ON = Manual mode, OFF = Automatic

// Street 1 (uses analog pins as digital)
const int R1_LED = A3;
const int Y1_LED = A4;
const int G1_LED = A5;

// Street 2
const int R2_LED = 5;
const int Y2_LED = 4;
const int G2_LED = 12;

// Street 3
const int R3_LED = 8;
const int Y3_LED = 7;
const int G3_LED = 6;

// Street 4
const int R4_LED = 11;
const int Y4_LED = 10;
const int G4_LED = 9;

// Buttons (hardware interrupts on Uno)
const int BTN_MODE   = 2;  // toggle Automatic/Manual
const int BTN_NEXT   = 3;  // advance in Manual

// ==== Timing (ms) ====
unsigned long GREEN_MS  = 1000;
unsigned long YELLOW_MS = 1000;
unsigned long RED_MS    = 1000;

// ==== State (used in ISRs → volatile) ====
volatile bool manualMode = false;   // false = Automatic, true = Manual
volatile bool stepNext   = false;   // set by BTN_NEXT in Manual

// Simple debounce for interrupts
volatile unsigned long lastIsrModeMs = 0;
volatile unsigned long lastIsrNextMs = 0;
const unsigned long ISR_DEBOUNCE_MS = 150;

// Utility: turn all Reds ON (safe baseline)
void allRed() {
  digitalWrite(R1_LED, HIGH);
  digitalWrite(R2_LED, HIGH);
  digitalWrite(R3_LED, HIGH);
  digitalWrite(R4_LED, HIGH);

  digitalWrite(Y1_LED, LOW);
  digitalWrite(Y2_LED, LOW);
  digitalWrite(Y3_LED, LOW);
  digitalWrite(Y4_LED, LOW);

  digitalWrite(G1_LED, LOW);
  digitalWrite(G2_LED, LOW);
  digitalWrite(G3_LED, LOW);
  digitalWrite(G4_LED, LOW);
}

// One street sequence (R,Y,G pins passed by value)
void street(int R, int Y, int G) {
  stepNext = false;          // reset per-street
  digitalWrite(R, LOW);      // red OFF for this street
  digitalWrite(G, HIGH);     // green ON

  if (manualMode) {
    // Wait until user presses "NEXT"
    while (!stepNext) {
      // You can add a small sleep to reduce CPU usage
      delay(5);
    }
    // Transition via yellow for 1s when leaving this street
    digitalWrite(G, LOW);
    digitalWrite(Y, HIGH);
    delay(YELLOW_MS);
    digitalWrite(Y, LOW);
    digitalWrite(R, HIGH);
    delay(RED_MS);
  } else {
    // Automatic timing
    delay(GREEN_MS);
    digitalWrite(G, LOW);

    digitalWrite(Y, HIGH);
    delay(YELLOW_MS);
    digitalWrite(Y, LOW);

    digitalWrite(R, HIGH);
    delay(RED_MS);
  }
}

// ==== ISRs ====
void isrToggleMode() {
  unsigned long now = millis();
  if (now - lastIsrModeMs < ISR_DEBOUNCE_MS) return;
  lastIsrModeMs = now;

  manualMode = !manualMode;            // toggle mode
  digitalWrite(LED_MODE, manualMode);  // blue LED reflects mode
}

void isrNextStep() {
  unsigned long now = millis();
  if (now - lastIsrNextMs < ISR_DEBOUNCE_MS) return;
  lastIsrNextMs = now;

  stepNext = true;                      // advance in manual mode
}

void setup() {
  // LEDs
  pinMode(LED_MODE, OUTPUT);

  pinMode(R1_LED, OUTPUT); pinMode(Y1_LED, OUTPUT); pinMode(G1_LED, OUTPUT);
  pinMode(R2_LED, OUTPUT); pinMode(Y2_LED, OUTPUT); pinMode(G2_LED, OUTPUT);
  pinMode(R3_LED, OUTPUT); pinMode(Y3_LED, OUTPUT); pinMode(G3_LED, OUTPUT);
  pinMode(R4_LED, OUTPUT); pinMode(Y4_LED, OUTPUT); pinMode(G4_LED, OUTPUT);

  allRed();
  digitalWrite(LED_MODE, LOW); // start in Automatic

  // Buttons (assumes external pull-down; signal rises when pressed)
  pinMode(BTN_MODE, INPUT);
  pinMode(BTN_NEXT, INPUT);

  attachInterrupt(digitalPinToInterrupt(BTN_MODE), isrToggleMode, RISING);
  attachInterrupt(digitalPinToInterrupt(BTN_NEXT), isrNextStep,   RISING);

  // If you're using internal pullups instead, use:
  // pinMode(BTN_MODE, INPUT_PULLUP);
  // pinMode(BTN_NEXT, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(BTN_MODE), isrToggleMode, FALLING);
  // attachInterrupt(digitalPinToInterrupt(BTN_NEXT), isrNextStep,   FALLING);
}

void loop() {
  // Run the sequence for each intersection
  street(R1_LED, Y1_LED, G1_LED);
  street(R2_LED, Y2_LED, G2_LED);
  street(R3_LED, Y3_LED, G3_LED);
  street(R4_LED, Y4_LED, G4_LED);
}
