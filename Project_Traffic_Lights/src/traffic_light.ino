// Traffic Light Control System (Arduino)
// Paste your actual project code here.
// Pin definitions and basic skeleton provided for convenience.

const int LED_BLUE = LED_BUILTIN; // status/mode LED (edit as needed)

void setup() {
  pinMode(LED_BLUE, OUTPUT);
  // TODO: define your Red/Yellow/Green pins for the 4 streets
  // TODO: attachInterrupt(...) for push buttons if used
  digitalWrite(LED_BLUE, LOW);
}

void loop() {
  // TODO: call your traffic sequence function for each street
  // Example placeholder:
  digitalWrite(LED_BLUE, HIGH);
  delay(500);
  digitalWrite(LED_BLUE, LOW);
  delay(500);
}
