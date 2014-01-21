/**
 * LedControl
 *
 * Command a blinking LED using a push button and a potentiometer to set 
 * the blinking speed.
 *
 * Date: 21/JAN/2014
 * Author: Rafael Winter
 *
 * Released under PUBLIC DOMAIN
 */



// Pins
#define PIN_PUSHBUTTON 2
#define PIN_BLUE_LED   3
#define PIN_RED_LED    4

// LED blinking steps limits
#define LED_BLINK_MIN  16
#define LED_BLINK_MAX  256



// Push button control variables
int lastButtonState = 0;
int currentButtonState = 0;

// Blue LED control variables
int isLedBlinking = LOW;
int ledState = LOW;
int shouldToggleLed = 0;

// Blue LED blinking control
unsigned long ledBlinkCounter = 0;
unsigned long ledBlinkSteps = 0;
unsigned long potentiometerValue = 0;


/**
 * Toggle the LED state to ON or OFF.
 */
void toggleLed() {
  if (shouldToggleLed) {

    // Toggle the LED state
    isLedBlinking = (isLedBlinking == LOW) ? HIGH : LOW;
    ledState = isLedBlinking;
    
    digitalWrite(PIN_BLUE_LED, ledState);
    
    shouldToggleLed = 0;
  } else {
    shouldToggleLed = 1;
  }
}

/**
 * Turn the LED ON or OFF according to the blinking speed
 *
 * Remarks: the LED only blinks when isLedBlinking is HIGH
 */
void blinkLed() {
  if (isLedBlinking == HIGH) {
    ledBlinkCounter++;
    if (ledBlinkCounter >= ledBlinkSteps) {
      ledState = (ledState == LOW) ? HIGH : LOW;
      digitalWrite(PIN_BLUE_LED, ledState);
      
      ledBlinkCounter = 0;
    }
  }
}

/**
 * Read the sensors used in the project
 */
void readSensors() {
  
  // Read the button and potentiometer states
  currentButtonState = digitalRead(PIN_PUSHBUTTON);
  potentiometerValue = analogRead(A0);
}

/**
 * Process the inputs and update states
 */
void update () {
  
  // Check if there is a button state change
  if (lastButtonState != currentButtonState) {
    
    // Update the current state and toggle the blue LED
    lastButtonState = currentButtonState;
    toggleLed();
  }
  
  // If the blue LED is blinking, update its state
  if (isLedBlinking == HIGH) {
    
    // Compute the current blink steps
    ledBlinkSteps = (potentiometerValue * LED_BLINK_MAX) / 1023;
    if (ledBlinkSteps < LED_BLINK_MIN) {
      ledBlinkSteps = LED_BLINK_MIN;
    }
    
    blinkLed();
  }
}

void setup() {
  
  pinMode(PIN_PUSHBUTTON, INPUT);
  pinMode(PIN_BLUE_LED, OUTPUT);
  pinMode(PIN_RED_LED, OUTPUT);

  // At this time the Red LED is always ON  
  digitalWrite(PIN_RED_LED, HIGH);
}

void loop() {
  
  // Read the button and potentiometer 
  readSensors();
  
  // Update the blue LED state
  update();
  
  // Delay in between reads for stability
  delay(1);        
}


    

