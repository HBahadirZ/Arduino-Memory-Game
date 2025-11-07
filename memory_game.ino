/*
  Arduino: Memory Game
  
  A 4-button, 4-LED memory game. The Arduino plays a sequence,
  and the player must repeat it. The sequence gets one step
  longer each round.
*/

// Pin Definitions
// Arrays for the pins make the code much cleaner
const int ledPins[] = {2, 3, 4, 5};     // Green, Red, Yellow, Blue
const int buttonPins[] = {8, 9, 10, 11}; // Green, Red, Yellow, Blue
const int buzzerPin = 12;

// Tones for the notes (C, G, E, A)
const int tones[] = {262, 392, 330, 440};

// Game Logic Variables
int gameSequence[100]; // An array to store the game's sequence
int level = 1;         // The current level (and length of sequence)
int playerIndex = 0;   // The index of the button the player is pressing

// Game States
enum GameState {
  START_UP,      // Waiting for the game to start
  COMPUTER_TURN, // Computer plays the sequence
  PLAYER_TURN,   // Player's turn to repeat
  GAME_OVER      // Player made a mistake
};

GameState currentState = START_UP; // Start in START_UP mode

// Setup: Runs only once at the beginning
void setup() {
  Serial.begin(9600); // For debugging
  
  // Initialize all the pins using for loops
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP); // Use the internal pull up resistor
  }
  pinMode(buzzerPin, OUTPUT);

  // Use a floating analog pin to get a true random number
  randomSeed(analogRead(A0)); 
  
  Serial.println("Game starts!"); // For debugging
} 

// Main Loop: Runs forever
void loop() {
  switch (currentState) {
    case START_UP:
      // Wait for any button press to start the game
      if (checkAnyButton()) {
        startGame();
      }
      break;

    case COMPUTER_TURN:
      playComputerTurn();
      break;

    case PLAYER_TURN:
      getPlayerTurn();
      break;

    case GAME_OVER:
      playGameOver();
      break;
  }
}

// Game Functions

void startGame() {
  level = 1;
  playerIndex = 0;
  currentState = COMPUTER_TURN; // Move to the computer's turn
}

void playComputerTurn() {
  Serial.print("Level "); // For debugging
  Serial.println(level);
  
  // Add one new random step to the sequence
  gameSequence[level - 1] = random(0, 4); // 0, 1, 2, or 3; each representing a color
  
  // Play back the entire sequence from the beginning
  for (int i = 0; i < level; i++) {
    int currentStep = gameSequence[i];
    flashLed(currentStep, 500); // Flash the LED for 500ms; decrease the value to increase the difficulty
    delay(150); // Pause between flashes
  }
  
  // Switch to the player's turn
  playerIndex = 0;
  currentState = PLAYER_TURN;
}

void getPlayerTurn() {
  // Check if any button is pressed
  int buttonPressed = checkButtons();

  if (buttonPressed != -1) { // A button was pressed
    Serial.print("Player pressed: "); // For debugging
    Serial.println(buttonPressed);

    flashLed(buttonPressed, 200); // Flash the button they pressed

    // Check if it is the correct button
    if (buttonPressed == gameSequence[playerIndex]) {
      // If it is correct
      playerIndex++; // Move to the next step in the sequence

      // Check if the player has finished the whole sequence
      if (playerIndex == level) {
        Serial.println("Level passed!");
        level++; // Next level!
        delay(1000); // Pause before the computer's next turn
        currentState = COMPUTER_TURN;
      }
      
    } else {
      // If it is not correct
      Serial.println("Game Over");
      currentState = GAME_OVER;
    }
  }
}

void playGameOver() {
  // Flash all lights and play a lose sound
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  tone(buzzerPin, 100, 1000); // Low tone
  delay(1000);
  
  // Turn all lights off
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  
  // Reset and wait for the next game
  delay(1000);
  currentState = START_UP;
  Serial.println("Press any button to start a new game");
}


// Helper Functions

// Flashes an LED and plays its corresponding tone
void flashLed(int index, int duration) {
  digitalWrite(ledPins[index], HIGH);
  tone(buzzerPin, tones[index], duration);
  delay(duration);
  digitalWrite(ledPins[index], LOW);
  noTone(buzzerPin);
}

// Checks if any button is pressed.
// Returns the index (0-3) or -1 if no button is pressed.
int checkButtons() {
  for (int i = 0; i < 4; i++) {
    // Since we are using input pullup LOW means pressed (active-low)
    if (digitalRead(buttonPins[i]) == LOW) {
      delay(50); // Simple debounce to prevent false reads
      
      // This loop does nothing (and holds the program)
      // until the button is no longer LOW (is released)
      while(digitalRead(buttonPins[i]) == LOW) {
        // do nothing
      }      
      return i; // return the button that was pressed
    }
  }
  return -1; // No button pressed
}
// A simple check for the start of the game
bool checkAnyButton() {
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      delay(50); // Debounce
      
      //  Wait for Release
      while(digitalRead(buttonPins[i]) == LOW) {
        // do nothing
      }      
      return true;
    }
  }
  return false;
}