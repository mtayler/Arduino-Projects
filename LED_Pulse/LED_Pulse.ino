#define LED (6)

void setup() {
  pinMode(LED, OUTPUT);
}

boolean debug = 1;
long prev = 0;
boolean state = HIGH;

void loop() {
  if (!debug) {
    if ((millis() - prev) > 100) {
      digitalWrite(LED, !state);
      state = !state;
      
      prev = millis();
    }
  }
  else {
    digitalWrite(LED, HIGH);
  }
}
