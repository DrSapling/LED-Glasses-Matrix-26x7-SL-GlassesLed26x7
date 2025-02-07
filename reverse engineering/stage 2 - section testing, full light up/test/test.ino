// List of pins for Charlieplexing
int pins[] = { 27, 14, 26, 25, 12, 13, 21, 23, 22, 17, 18, 5, 19,     4, 16, 15 };
int numPins = sizeof(pins) / sizeof(pins[0]);

void setup() {
  // set all pins to low before
  for (int i = 0; i < numPins; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }
}

void loop() {
  // There are 13 sections: pin 27-19

  for (int section = 0; section < 14; section++) { // For each section (13 times)

    digitalWrite(pins[section], HIGH); // "Section" pin to HIGH
    // For each section all the lights will light up

    for (int led = 0; led < 14; led++) { // For each led in section (14 times)

      if (pins[section] == pins[led]) { // If section-pin the same as led-pin

        if (section % 2 == 0) {
          digitalWrite(pins[14], LOW); // 16th pin LOW
          pinMode(pins[15], INPUT); // 15th pin disable
        }
        else {
          digitalWrite(pins[15], LOW); // 15th pin LOW
          pinMode(pins[14], INPUT); // 16th pin disable
        }

      }
      else { // If section-pin different than led-pin
        digitalWrite(pins[led], LOW);
      }
    }

    delay(10);
    for (int i = 0; i < numPins; i++) {
      pinMode(pins[i], OUTPUT);
      digitalWrite(pins[i], LOW); // clear before showing next section
    }
  }
}
