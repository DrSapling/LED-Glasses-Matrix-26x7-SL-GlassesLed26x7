// List of pins for Charlieplexing
//
//                     0   1   2   3   4   5   6   7   8   9   10  11  12    13  14  15
const short pins[] = { 27, 14, 26, 25, 12, 13, 21, 23, 22, 17, 18, 5, 19,     4, 16, 15 };    // 4, 16, 15 are used only for digital low
const short numPins = sizeof(pins) / sizeof(pins[0]);
         
const unsigned short bitmap_testface[13] PROGMEM = {
    0b0011100000001011,
    0b0000011110110100,
    0b0000101101111000,
    0b0011010000000111,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0011100000001011,
    0b0000011110110100,
    0b0000101101111000,
    0b0011010000000111
};





void setup() {

  // Set all pins to INPUT by default
  for (int i = 0; i < numPins; i++) {
    pinMode(pins[i], INPUT);
  }
  
  //const unsigned short selected_face* = bitmap_testface;
}



void loop() {

  // two times: for pin 14th and 15th pins

  // for 14th pin: iterate through 7 sections, starting form 0th
  for (int section = 0; section <= 12; section+=2) {
    drawSectionEvenPin(section);
    delayMicroseconds(1000);
    resetAllPins();
  }
  // for 15th pin: iterate through 6 sections, startinf from 1st
  for (int section = 1; section <= 11; section+=2) {
    drawSectionOddPin(section);
    delayMicroseconds(1000);
    resetAllPins();
  }
}



void drawSectionEvenPin(int SECTION_PIN) {
  //pinMode(pins[SECTION_PIN], OUTPUT);
  //digitalWrite(pins[SECTION_PIN], HIGH);
  //pinMode(pins[SECTION_PIN], INPUT);
  for (int led_pin = 0; led_pin < numPins-2; led_pin++) {
    if (led_pin != SECTION_PIN) {
      if (bitmap_testface[SECTION_PIN] & (1 << led_pin)) {
        pinMode(pins[led_pin], OUTPUT);
        //delay(100);
        digitalWrite(pins[led_pin], LOW);
        //delay(100);
      }
      // else {
      //   pinMode(pins[led_pin], INPUT_PULLUP);
      //   //delay(100);
      // }
    }
    else {
      if (bitmap_testface[SECTION_PIN] & (1 << led_pin)) {
        pinMode(pins[14], OUTPUT);
        //delay(100);
        digitalWrite(pins[14], LOW);
        //delay(100);
      }
      // else {
      //   pinMode(pins[14], INPUT_PULLUP);
      //   //delay(100);
      // }
    }
  }
  pinMode(pins[SECTION_PIN], OUTPUT);
  //delay(100);
  digitalWrite(pins[SECTION_PIN], HIGH);
  //delay(100);
}

void drawSectionOddPin(int SECTION_PIN) {
  //pinMode(pins[SECTION_PIN], OUTPUT);
  //digitalWrite(pins[SECTION_PIN], HIGH);
  //pinMode(pins[SECTION_PIN], INPUT);
  for (int led_pin = 0; led_pin < numPins-2; led_pin++) {
    if (led_pin != SECTION_PIN) {
      if (bitmap_testface[SECTION_PIN] & (1 << led_pin)) {
        pinMode(pins[led_pin], OUTPUT);
        //delay(100);
        digitalWrite(pins[led_pin], LOW);
        //delay(100);
      }
      // else {
      //   pinMode(pins[led_pin], INPUT_PULLUP);
      //   //delay(100);
      // }
    }
    else {
      if (bitmap_testface[SECTION_PIN] & (1 << led_pin)) {
        pinMode(pins[15], OUTPUT);
        //delay(100);
        digitalWrite(pins[15], LOW);
        //delay(100);
      }
      // else {
      //   pinMode(pins[15], INPUT_PULLUP);
      //   //delay(100);
      // }
    }
  }
  pinMode(pins[SECTION_PIN], OUTPUT);
  //delay(100);
  digitalWrite(pins[SECTION_PIN], HIGH);
  //delay(100);
}

void resetAllPins(){
  for (int i = 0; i < numPins; i++) {
      digitalWrite(pins[i], LOW);
      pinMode(pins[i], INPUT);
    }
}