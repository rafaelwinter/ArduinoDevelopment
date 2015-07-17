/**
 * KEYES 5050 LED module test
 *
 * Command a KEYES 5050 LED module by lighting one LED at time and 
 * interpolating between the rainbow colors
 *
 * Date: 17/JUL/2015
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
const int kDelay = 75;

// Some rainbow colors <3
const long kColorPalette[] = {
  0xFF0000, // Red
  0xFF8C00, // Orange
  0xFFFF00, // Yellow
  0x00FF00, // Green
  0x0000FF, // Blue
  0x4B0082, // Indigo
  0xD02090, // Violet
};

const float kColorStep = 1.0f / (kLastPin - kFirstPin + 1);

int currentLed;
int increase;

int currentColor;
int nextColor;
float colorMix;
float colorStep;

void setup() {

  // Setup each pin used to light on the 5050 module
  for (int i = kFirstPin; i <= kLastPin; i++) {
    pinMode(i, OUTPUT);
  }

  // Setup the anode pins, used to control the color
  pinMode(kRedPin, OUTPUT);
  pinMode(kGreenPin, OUTPUT);
  pinMode(kBluePin, OUTPUT);

  // Sets the first led, movement direction and the first color
  currentLed = kFirstPin;
  increase = 1;
  currentColor = 0;
  nextColor = 1;
  colorMix = 0.0f;
}

void loop() {

  // Light off and on each led, according to the currently lit LED
  for (int i = kFirstPin; i <= kLastPin; i++) {
    if (i == currentLed) {
      digitalWrite(i, LOW);
    } else {
      digitalWrite(i, HIGH);
    }
  }

  currentLed += increase;
  colorMix += kColorStep;

  // Check if the current led is out of bounds
  if (currentLed < kFirstPin || currentLed > kLastPin) {

    // Invert the movement and set the current led
    increase *= -1;
    currentLed += (increase * 2);

    // Increase the current and next color
    currentColor = ++currentColor % (sizeof(kColorPalette) / sizeof(long));
    nextColor = (currentColor + 1) % (sizeof(kColorPalette) / sizeof(long));

    colorMix = 0.0f;
  }

  // Mix individually the RED color channel
  long currentRed = (kColorPalette[currentColor] & 0x00FF0000) >> 16;
  long nextRed = (kColorPalette[nextColor] & 0x00FF0000) >> 16;
  long redIntensity = (long) lerp(currentRed, nextRed, colorMix);

  // Mix individually the GREEN color channel  
  long currentGreen = (kColorPalette[currentColor] & 0x0000FF00) >> 8;
  long nextGreen = (kColorPalette[nextColor] & 0x0000FF00) >> 8;
  long greenIntensity = (long) lerp(currentGreen, nextGreen, colorMix);

  // Mix individually the BLUE color channel
  long currentBlue = (kColorPalette[currentColor] & 0x000000FF);
  long nextBlue = (kColorPalette[nextColor] & 0x000000FF);
  long blueIntensity = (long) lerp(currentBlue, nextBlue, colorMix);

  // Set the RGB pins. Please note that since it's negative, we must invert
  // by subtracting from 255
  analogWrite(kRedPin, 255 - redIntensity);
  analogWrite(kGreenPin, 255 - greenIntensity);
  analogWrite(kBluePin, 255 - blueIntensity);

  // Let the thing breath for a while
  delay(kDelay);
}

// See https://en.wikipedia.org/wiki/Linear_interpolation
// Precise method which guarantees v = v1 when t = 1.
float lerp(float v0, float v1, float t) {
  return (1.0f - t) * v0 + t * v1;
}

