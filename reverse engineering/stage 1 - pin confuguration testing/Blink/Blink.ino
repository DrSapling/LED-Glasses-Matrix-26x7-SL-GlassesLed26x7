// List of pins for Charlieplexing
int pins[] = { 27, 14, 26, 25, 12, 13, 21, 23, 22, 17, 18, 5, 19,     4, 16, 15 };
int numPins = sizeof(pins) / sizeof(pins[0]);

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  while (!Serial) {
    // Wait for the serial monitor to connect (useful for boards like Arduino Leonardo)
  }

  // Set all pins to INPUT by default
  for (int i = 0; i < numPins; i++) {
    pinMode(pins[i], INPUT);
  }

  Serial.println("LED control ready.");
  Serial.println("Send commands in the format 'pin.state' (e.g., '14.h', '14.l', '14.d').");
  Serial.println("State options: 'h' = HIGH, 'l' = LOW, 'd' = INPUT.");
}

void loop() {
  // Check for serial input
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); // Read the input until a newline
    command.trim(); // Remove any extra spaces or newline characters

    // Parse the command (format: "pin.state")
    int dotIndex = command.indexOf('.');
    if (dotIndex != -1) {
      String pinStr = command.substring(0, dotIndex);   // Extract the pin number as a string
      String stateStr = command.substring(dotIndex + 1); // Extract the state part

      int pin = pinStr.toInt(); // Convert the pin number to an integer
      char state = stateStr[0]; // Get the state character ('h', 'l', or 'd')

      // Validate the pin
      if (isValidPin(pin)) {
        // Execute the command based on the state
        if (state == 'h') {
          pinMode(pin, OUTPUT);
          digitalWrite(pin, HIGH);
          Serial.print("Pin ");
          Serial.print(pin);
          Serial.println(" set to HIGH.");
        } else if (state == 'l') {
          pinMode(pin, OUTPUT);
          digitalWrite(pin, LOW);
          Serial.print("Pin ");
          Serial.print(pin);
          Serial.println(" set to LOW.");
        } else if (state == 'd') {
          pinMode(pin, INPUT);
          Serial.print("Pin ");
          Serial.print(pin);
          Serial.println(" set to INPUT.");
        } else {
          Serial.println("Invalid state. Use 'h', 'l', or 'd'.");
        }
      } else {
        Serial.println("Invalid pin. Please use one of the defined pins.");
      }
    } else {
      Serial.println("Invalid command format. Use 'pin.state'.");
    }
  }
}

// Helper function to check if the pin is in the list
bool isValidPin(int pin) {
  for (int i = 0; i < numPins; i++) {
    if (pins[i] == pin) {
      return true;
    }
  }
  return false;
}
