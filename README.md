## Arduino: Memory Game

This is a classic 4-button, 4-LED memory game built with an Arduino. The Arduino plays a sequence of lights and sounds, and the player must repeat the sequence. The sequence gets one step longer each round, increasing the difficulty.

![PXL_20251107_012949480](https://github.com/user-attachments/assets/336585d6-2313-4cb2-b2a8-28a88397444d)

## 🚀 How to Play

Power On: Connect power to the Arduino.

Start Game: Press any of the four buttons to start the game.

Watch & Listen: The Arduino will play the first step of the sequence (e.g., "Green").

Repeat: Press the button that just lit up ("Green").

Level Up: The Arduino will repeat the first step and add a new one (e.g., "Green," "Red").

Repeat Again: You must press the buttons in the correct order ("Green," then "Red").

Keep Going: The game continues until you make a mistake.

Game Over: If you press the wrong button, a "game over" sound will play, and all lights will flash.

New Game: Press any button to start a new game!

## ✨ Features

Progressive Difficulty: The sequence gets one item longer after each successful level.

Audio & Visual Feedback: Each button has a corresponding LED and a unique tone that plays.

Game Over State: A clear signal lets you know when you've made a mistake.

Randomized Sequences: Uses the Arduino's random() function to generate a different game every time.

Simple Wiring: Uses the Arduino's internal INPUT_PULLUP resistors, so you don't need external resistors for your buttons.

## 🛠️ Hardware Required

1x Arduino (Uno, Nano, or any compatible board)

4x LEDs (Green, Red, Yellow, Blue recommended)

4x Pushbuttons

4x Resistors (220Ω or 330Ω for the LEDs)

1x Piezo Buzzer

1x Breadboard

Jumper Wires

Power Source (USB or 9V battery)

##🔌 Wiring & Assembly

The circuit is wired according to the pin definitions in the Arduino sketch.

Pin Definitions

LEDs (Pins 2, 3, 4, 5):

Green LED: Pin 2 -> Resistor -> LED Anode (+) | LED Cathode (-) -> GND

Red LED: Pin 3 -> Resistor -> LED Anode (+) | LED Cathode (-) -> GND

Yellow LED: Pin 4 -> Resistor -> LED Anode (+) | LED Cathode (-) -> GND

Blue LED: Pin 5 -> Resistor -> LED Anode (+) | LED Cathode (-) -> GND

Buttons (Pins 8, 9, 10, 11):

This project uses INPUT_PULLUP, which simplifies wiring.

Green Button: One leg to Pin 8 | Other leg to GND

Red Button: One leg to Pin 9 | Other leg to GND

Yellow Button: One leg to Pin 10 | Other leg to GND

Blue Button: One leg to Pin 11 | Other leg to GND

Buzzer (Pin 12):

Buzzer Positive (+): Pin 12

Buzzer Negative (-): GND

## 💻 Software

The complete, commented code is in the .ino file.

Main Logic: The game runs on a switch statement that manages four game states:

START_UP: Waits for a button press to begin.

COMPUTER_TURN: Plays the current sequence and adds one new step.

PLAYER_TURN: Waits for the player to input the sequence.

GAME_OVER: Plays an error sound/light show and resets.

Button Handling: The checkButtons() function detects a button press. It includes a while loop to wait for the button to be released. This is a simple and effective form of debouncing and prevents one long press from being read multiple times.

## Here is a video demonstration!

https://github.com/user-attachments/assets/0ef4c370-33d4-46b4-bb9c-a31558a16912
