// ALL FACES
const unsigned short bitmap_XX[13] PROGMEM = {
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
const unsigned short bitmap_AA[13] PROGMEM = {
    0b0011101000000000,
    0b0000010111111010,
    0b0000101011110101,
    0b0011010100000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0011101000000000,
    0b0000010111111010,
    0b0000101011110101,
    0b0011010100000000
};
const unsigned short bitmap_grr[13] PROGMEM = {
    0b0000000000001011,
    0b0000000010110100,
    0b0000101101000000,
    0b0011010000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0011100000000000,
    0b0000011110000000,
    0b0000000001111000,
    0b0000000000000111
};
const unsigned short bitmap_Oo[13] PROGMEM = {
    0b0000101010101000,
    0b0011010101010111,
    0b0011000000000011,
    0b0001111111111101,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000101111111000,
    0b0000110000001100,
    0b0000011111110100,
    0b0000000000000000
};

// List of pins for Charlieplexing
//           order     1   2   3   4   5   6   7   8   9   10  11  12  13    14  15  16
//           index     0   1   2   3   4   5   6   7   8   9   10  11  12    13  14  15
const short pins[] = { 27, 14, 26, 25, 12, 13, 21, 23, 22, 17, 18, 5, 19,     4, 16, 15 };    // 4, 16, 15 are used only for digital low
const short numPins = sizeof(pins) / sizeof(pins[0]);

unsigned long micros_display_update = 0;
short section = 0;   // for keeping track of next section on display to update (like i in for loop)
const unsigned short *selected_face_ptr = bitmap_XX;

unsigned long millis_face_counter = 0;
short face_counter = 0;




void setup() {

  resetAllPins();

}



void loop() {

  // DISPLAY UPDATE - every 1ms
  
  if (micros() >= micros_display_update + 1000) {

    micros_display_update = micros();
    resetAllPins();

    if (section > 12)
      section = 0;

    if (section % 2 == 0)
      drawSectionEvenPin(section, selected_face_ptr);
    else
      drawSectionOddPin(section, selected_face_ptr);

    section++;
  }



  // FACE CHANGE - every 1s
  if (millis() >= millis_face_counter + 1000) {
    millis_face_counter = millis();

    switch(face_counter++) {
      case 0:
        selected_face_ptr = bitmap_AA;
        break;
      case 1:
        selected_face_ptr = bitmap_Oo;
        break;
      case 2:
        selected_face_ptr = bitmap_grr;
        break;
      case 3:
        selected_face_ptr = bitmap_XX;
        face_counter = 0;
        break;
    }
    //face_counter++;
  }
}



void drawSectionEvenPin(int SECTION_PIN, const unsigned short *FACE) {
  for (int led_pin = 0; led_pin < numPins-2; led_pin++) {
    if (led_pin != SECTION_PIN) {
      if (FACE[SECTION_PIN] & (1 << led_pin)) {
        pinMode(pins[led_pin], OUTPUT);
        digitalWrite(pins[led_pin], LOW);
      }
    }
    else {
      if (FACE[SECTION_PIN] & (1 << led_pin)) {
        pinMode(pins[14], OUTPUT);
        digitalWrite(pins[14], LOW);
      }
    }
  }
  pinMode(pins[SECTION_PIN], OUTPUT);
  digitalWrite(pins[SECTION_PIN], HIGH);
}

void drawSectionOddPin(int SECTION_PIN, const unsigned short *FACE) {
  for (int led_pin = 0; led_pin < numPins-2; led_pin++) {
    if (led_pin != SECTION_PIN) {
      if (FACE[SECTION_PIN] & (1 << led_pin)) {
        pinMode(pins[led_pin], OUTPUT);
        digitalWrite(pins[led_pin], LOW);
      }
    }
    else {
      if (FACE[SECTION_PIN] & (1 << led_pin)) {
        pinMode(pins[15], OUTPUT);
        digitalWrite(pins[15], LOW);
      }
    }
  }
  pinMode(pins[SECTION_PIN], OUTPUT);
  digitalWrite(pins[SECTION_PIN], HIGH);
}

void resetAllPins(){
  for (int i = 0; i < numPins; i++) {
      digitalWrite(pins[i], LOW);
      pinMode(pins[i], INPUT);
    }
}