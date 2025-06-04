/*
 * This Arduino sketch controls a seven-segment display to count from 0 to 9
 * with a one-second delay between each digit. The display is a common anode
 * type, so the segments are turned on by setting the corresponding pins to LOW.
 */

const int segmentPins[] = {2, 3, 4, 5, 6, 7, 8}; // Pins connected to segments A-G

// Digit patterns for common anode 7-segment display (0-9)
const byte digitPatterns[10] = {
  0b11000000, // 0
  0b11111001, // 1
  0b10100100, // 2
  0b10110000, // 3
  0b10011001, // 4
  0b10010010, // 5
  0b10000010, // 6
  0b11111000, // 7
  0b10000000, // 8
  0b10010000  // 9
};

void setup() {
  // Initialize segment pins as outputs
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
}

void loop() {
  for (int digit = 0; digit < 10; digit++) {
    displayDigit(digit);
    delay(1000); // Wait for 1 second
  }
}

void displayDigit(int digit) {
  byte pattern = digitPatterns[digit];
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], (pattern & (1 << i)) ? HIGH : LOW);
  }
}
