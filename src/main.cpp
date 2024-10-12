/**
 * @file main.cpp
 * @brief Game logic for an Arduino-based game using an LCD screen.
 * 
 * This code handles the game setup, game loop, and states such as idle, playing,
 * and game over. It displays the game on an LCD screen and manages the 
 * interaction with a button for jumping and restarting the game.
 * 
 * @author WittyWizard
 * @date 2024-10-12
 */

#include <Arduino.h>

#ifdef I2C_LCD
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#else
#include <LiquidCrystal.h>
#endif

#include "definitions.h"
#include "functions.h"
#include "variables.h"

/**
 * @brief Arduino setup function.
 * 
 * This function initializes the LCD screen and sets up the button input and 
 * interrupt for handling jumps in the game.
 */
void setup() {
  setupLCD();  // Initializes the LCD
  pinMode(BTN_PIN, INPUT_PULLUP);  // Configures button pin with internal pull-up
  attachInterrupt(digitalPinToInterrupt(BTN_PIN), jump, FALLING);  // Attach interrupt to the button
}

/**
 * @brief Arduino loop function.
 * 
 * Main game loop that handles the different game states, such as waiting for the
 * player to start, playing the game, and game over state. The game logic for
 * moving obstacles, checking for collisions, and scoring is also implemented here.
 */
void loop() {
  switch (currentState) {
    case FIRST_START:
      lcd.print("Press to start");  // Initial prompt for user input
      currentState = IDLE;  // Set state to idle
      break;

    case PLAYING:
      // Spawn trees if positions are empty
      if (tree0 <= 0) {
        spawnTree(tree0, tree3);
      }
      if (tree1 <= 0) {
        spawnTree(tree1, tree0);
      }
      if (tree2 <= 0) {
        spawnTree(tree2, tree1);
      }
      if (tree3 <= 0) {
        spawnTree(tree3, tree2);
      }

      lcd.clear();  // Clear the LCD screen

      // Handle dinosaur jump and collision detection
      switch (currentJump) {
        case JUMP:
          lcd.setCursor(DINOSAUR_POSITION, DISPLAY_TOP);
          score++;  // Increment score on successful jump
          currentJump = NO_JUMP;
          break;

        default:
          lcd.setCursor(DINOSAUR_POSITION, DISPLAY_BOTTOM);
          if (collisionCheck(tree0) || collisionCheck(tree1) ||
              collisionCheck(tree2) || collisionCheck(tree3)) {
            currentState = GAME_OVER;  // Switch to game over if collision detected
            break;
          } else {
            score++;  // Increment score if no collision
          }
          break;
      }

      if (currentState == GAME_OVER) {
        break;
      }

      // Display dinosaur and trees on the LCD
      displaydinosour();
      displayTree(tree0);
      displayTree(tree1);
      displayTree(tree2);
      displayTree(tree3);

      // Move trees (decrease position)
      tree0--;
      tree1--;
      tree2--;
      tree3--;
      delay(GAME_SPEED);  // Delay based on game speed
      break;

    case GAME_OVER:
      high_score = max(score, high_score);  // Update high score

      lcd.clear();  // Clear the LCD screen
      lcd.setCursor(collision_tree + 1, DISPLAY_BOTTOM);
      lcd.write((uint8_t)TREE);
      lcd.setCursor(collision_tree, DISPLAY_BOTTOM);
      lcd.write((uint8_t)DINOR);
      delay(300);
      lcd.clear();
      delay(600);
      lcd.setCursor(collision_tree + 1, DISPLAY_BOTTOM);
      lcd.write((uint8_t)TREE);
      lcd.setCursor(DINOSAUR_POSITION, DISPLAY_BOTTOM);
      lcd.write((uint8_t)DINOR);
      delay(600);
      lcd.clear();
      delay(500);
      lcd.setCursor(collision_tree + 1, DISPLAY_BOTTOM);
      lcd.write((uint8_t)TREE);
      lcd.setCursor(DINOSAUR_POSITION, DISPLAY_BOTTOM);
      lcd.write((uint8_t)DINOR);
      delay(600);
      lcd.clear();
      delay(600);
      lcd.print("High Score: ");
      lcd.print(high_score);  // Display high score
      lcd.setCursor(0, DISPLAY_BOTTOM);
      lcd.print("Score: ");
      lcd.print(score);  // Display current score
      delay(1500);
      lcd.clear();
      delay(400);
      lcd.setCursor(0, DISPLAY_TOP);
      lcd.print("Press Again to");
      lcd.setCursor(0, DISPLAY_BOTTOM);
      lcd.print("Play");
      score = 0;  // Reset score for the next game
      currentState = IDLE;  // Set state to idle
      break;

    default:
      break;
  }
}
