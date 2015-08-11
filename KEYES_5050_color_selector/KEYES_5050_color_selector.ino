/**
 * KEYES 5050 color selector
 *
 * Command a KEYES 5050 LED module by selecting a color
 * from the predefined palette using a potentiometer
 *
 * Date: 19/JUL/2015
 * Author: Rafael Winter - https://github.com/rafaelwinter
 *
 * Released under PUBLIC DOMAIN
 */

// The first and last digital pins used to light up the KEYES 5050 module.
// They are connected from D0 to D10 in the module board.
const int kFirstPin = 2;
const int kLastPin = 9;

// The digital pins used to control the color.
// They are conected to the pins R, G and B of the KEYES 5050 module board.
// There are some boards with wrong pin naming printed, in my case the board
// shows R, B, G, you may ignore it as well.
const int kRedPin = 10;
const int kGreenPin = 11;
const int kBluePin = 12;

// Delay between each loop cycle
const int kDelay = 100;

// Some RGB colors in the format 0xRRGGBB
const long kColorPalette[] = {
  0xFF0000, // Red
  0xFF8C00, // Orange
  0xFFFF00, // Yellow
  0x00FF00, // Green
  0x0000FF, // Blue
  0x4B0082, // Indigo
  0xD02090, // Violet
  0x9F00FF, // Vivid Violet
  0xFFFFFF, // White 
};

float colorInterval;

int colorIndex = 0;

void setup() {

  // Light up all 5050 module LEDS
  for (int i = kFirstPin; i <= kLastPin; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

  pinMode(LED_BUILTIN, OUTPUT);

  // Setup the anode pins, used to control the color
  pinMode(kRedPin, OUTPUT);
  pinMode(kGreenPin, OUTPUT);
  pinMode(kBluePin, OUTPUT);

  int paletteLength = (sizeof(kColorPalette) / sizeof(long));
  colorInterval = 1023 / (float) (paletteLength - 1);
}

void loop() {

  for (int i = kFirstPin; i <= kLastPin; i++) {
    digitalWrite(i, LOW);
  }
  
  int potentiometerValue = 1023 - analogRead(A0);
  int currentColor = round(potentiometerValue / colorInterval);

  digitalWrite(LED_BUILTIN, (currentColor % 2) ? HIGH : LOW);
  
  if (currentColor != colorIndex) {
    colorIndex = currentColor;

    // Get the intensity of each color channel
    long redIntensity = (kColorPalette[currentColor] & 0x00FF0000) >> 16;
    long greenIntensity = (kColorPalette[currentColor] & 0x0000FF00) >> 8;
    long blueIntensity = (kColorPalette[currentColor] & 0x000000FF);
  
    // Set the RGB pins. Please note that since it's negative, we must invert
    // by subtracting from 255
    analogWrite(kRedPin, 255 - redIntensity);
    analogWrite(kGreenPin, 255 - greenIntensity);
    analogWrite(kBluePin, 255 - blueIntensity);
  }
  
  // Let the thing breath for a while
  delay(kDelay);
}

