#define LED (6)
#define BUTTON1 (2)
#define BUTTON2 (3)
#define BUTTON3 (4)

#define NONE (0)

byte state = NONE;
bool led_state = LOW;

long prev = millis();

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!digitalRead(BUTTON1) && state != BUTTON1) {
    state = BUTTON1;
    Serial.println("BUTTON1");
  }
  else if (!digitalRead(BUTTON2) && state != BUTTON2) {
    state = BUTTON2;
    Serial.println("BUTTON2");
    digitalWrite(LED, LOW);
  }
  else if (!digitalRead(BUTTON3) && state != BUTTON3) {
    state = BUTTON3;
    Serial.println("BUTTON3");
    digitalWrite(LED, HIGH);
  }
  
  switch (state) {
    case NONE:
      break;
    case BUTTON1:
      digitalWrite(LED, HIGH);
      break;
    case BUTTON2:
      pulse(10);
      break;
    case BUTTON3:
      pulse(50);
      break;
  }
}

void pulse(byte hertz) {
  if (millis() - prev < (1.0/hertz)) {
    digitalWrite(LED, !led_state);
    led_state = !led_state;
    prev = millis();
  }
}
