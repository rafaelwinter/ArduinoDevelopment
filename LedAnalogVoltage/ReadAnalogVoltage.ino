int leds[] = {9,10,11};
int ledsCount = 3;
double maxLedBright = 255.0;
double maxInputBright;
float x;

void setup() {
  Serial.begin(9600); 
  for(int i = 0; i < ledsCount; i++){
    pinMode(leds[i], OUTPUT);
  }
  x = 1023.0/ledsCount;
  maxInputBright = (maxLedBright * ledsCount);
  
}

void loop() {
   
  int sensor = analogRead(A1);
  /*Value of brightness... max of 381*/

  //The value of the input for the last LED
  float inputBright = sensor * (maxInputBright / 1023.0);
//  analogWrite(3, inputBright);

  //How many leds are on
  double onValue = sensor * (ledsCount / 1023.0);
  int onLeds = (int)onValue;

  //Turn off exceeding leds
  for(int i = ledsCount-1; i >= onLeds; i--) {
    digitalWrite(leds[i], LOW);
  } 

  //The last led will be in the index marked in ON LEDS
  int lastLed = onLeds;
  for(int i = 0; i < onLeds; i++) {
    digitalWrite(leds[i], HIGH);
  }
  int lastLedBright = (int)fmod(inputBright,maxLedBright);
  if(inputBright > 0.500){
    analogWrite(leds[lastLed], lastLedBright);
  }
//  Serial.println(">>"); 
//  Serial.print("Last Led :");
//  Serial.print(lastLed);
  Serial.print(" Bright:");
  Serial.print(inputBright);  
  Serial.print(" on:");
  Serial.print(onLeds);  
  Serial.print(" LED BRIGHT:");
  Serial.print(lastLedBright);
  Serial.println(""); 
  delay(10);
}
