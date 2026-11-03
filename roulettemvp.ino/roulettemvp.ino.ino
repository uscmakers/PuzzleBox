// Rigged Arduino LED Roulette Wheel

const int ledPins[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
const int numLeds = 10;
const int buttonPin = 12;

// Set the exact LED index you ALWAYS want to win (0 to 9)
// 0 = Pin 2, 1 = Pin 3, 2 = Pin 4 ... 9 = Pin 11
const int FORCED_WINNING_INDEX = 4; 

void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  pinMode(buttonPin, INPUT_PULLUP);
  
  // Seed random generator strictly to vary full rotation counts for realism
  randomSeed(analogRead(A0));
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    spinRoulette();
    delay(300); // Debounce delay
  }
}

void spinRoulette() {
  // Always use the hardcoded target
  int targetIndex = FORCED_WINNING_INDEX;
  
  // Vary rotations (3 to 5 full circles) so spin length varies naturally
  int fullRotations = random(3, 6); 
  int totalSteps = (fullRotations * numLeds) + targetIndex;
  
  int stepDelay = 20;

  for (int step = 0; step < totalSteps; step++) {
    int currentLed = step % numLeds;

    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], LOW);
    }

    digitalWrite(ledPins[currentLed], HIGH);
    delay(stepDelay);

    // Apply deceleration curve
    int remainingSteps = totalSteps - step;
    if (remainingSteps < 15) {
      stepDelay += 20;
    } else if (remainingSteps < 30) {
      stepDelay += 8;
    }
  }

  // Flash winning LED
  int winningPin = ledPins[targetIndex];
  for (int f = 0; f < 6; f++) {
    digitalWrite(winningPin, LOW);
    delay(150);
    digitalWrite(winningPin, HIGH);
    delay(150);
  }
}