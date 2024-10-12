/**
 * @file functions.cpp
 * @brief Implementation of game logic and hardware control functions.
 * 
 * This file implements the functions responsible for handling the LCD display, spawning and
 * displaying trees, moving the dinosaur, checking for collisions, and managing the player's 
 * input (jump action).
 * 
 * @author WittyWizard
 * @date 2024-10-12
 */

#include "functions.h"
#include "definitions.h"
#include "variables.h"

#ifdef I2C_LCD
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#else
#include <LiquidCrystal.h>
#endif

/**
 * @brief Initializes the LCD display based on the type of connection (I2C or parallel).
 * 
 * Sets up the LCD display by initializing the screen and configuring the custom characters
 * (dinosaur and tree) for later use in the game.
 */
void setupLCD() {
#ifdef I2C_LCD
  lcd.init();        ///< Initializes the I2C LCD
  lcd.backlight();   ///< Turns on the LCD backlight
#else
  lcd.begin(16, 2);  ///< Initializes the standard 16x2 LCD
#endif
  lcd.createChar(TREE, tree);    ///< Creates the tree character
  lcd.createChar(DINOR, dinor);  ///< Creates the right-facing dinosaur character
  lcd.createChar(DINOL, dinol);  ///< Creates the left-facing dinosaur character
  lcd.setCursor(0, 0);           ///< Sets the cursor to the top-left corner
}

/**
 * @brief Spawns a tree at a random position relative to a previous tree.
 * 
 * This function uses a random number generator to place the tree at a location
 * within a defined range, ensuring that trees are not too close or too far apart.
 * 
 * @param tree The reference to the tree being spawned.
 * @param tree_previous The reference to the previous tree to maintain distance constraints.
 */
void spawnTree(uint8_t &tree, uint8_t &tree_previous) {
  randomSeed(analogRead(A0));  ///< Seeds the random number generator with analog input
  tree = random(MIN_TREE_DISTANCE, MAX_TREE_DISTANCE) + tree_previous;  ///< Sets the new tree position
}

/**
 * @brief Displays a tree on the LCD screen.
 * 
 * If the tree is within the bounds of the display, it is drawn at its current position
 * on the bottom row of the screen.
 * 
 * @param tree The reference to the tree's current position.
 */
void displayTree(uint8_t &tree) {
  if (tree <= DISPLAY_X) {
    lcd.setCursor(tree, DISPLAY_BOTTOM);  ///< Sets the cursor to the tree's position
    lcd.write((uint8_t)TREE);             ///< Draws the tree character
  }
}

/**
 * @brief Displays the dinosaur on the LCD screen.
 * 
 * Alternates between displaying the left-facing and right-facing dinosaur characters
 * to simulate movement.
 */
void displaydinosour() {
  switch (currentMotion) {
    case LEFT:
      lcd.write((uint8_t)DINOL);  ///< Displays the left-facing dinosaur
      currentMotion = RIGHT;      ///< Switches to right-facing for the next display
      break;

    default:
      lcd.write((uint8_t)DINOR);  ///< Displays the right-facing dinosaur
      currentMotion = LEFT;       ///< Switches to left-facing for the next display
      break;
  }
}

/**
 * @brief Checks for a collision between the dinosaur and a tree.
 * 
 * If a tree is in the same position as the dinosaur, a collision is detected and
 * the collision position is stored.
 * 
 * @param tree The reference to the tree's current position.
 * @return True if a collision is detected, false otherwise.
 */
bool collisionCheck(uint8_t &tree) {
  if (tree == DINOSAUR_POSITION) {
    collision_tree = tree;  ///< Stores the tree position where the collision occurred
  }
  return (tree == DINOSAUR_POSITION);  ///< Returns true if the dinosaur's position matches the tree's position
}

#if defined(ARDUINO_ARCH_ESP8266)
/**
 * @brief Interrupt Service Routine (ISR) for handling the dinosaur's jump on ESP8266.
 * 
 * This function is called when the jump button is pressed. It handles the transition
 * between game states and sets the jump state when the game is in progress.
 */
void IRAM_ATTR jump()
#elif defined(ARDUINO_ARCH_AVR)
/**
 * @brief Interrupt Service Routine (ISR) for handling the dinosaur's jump on AVR.
 * 
 * This function is called when the jump button is pressed. It handles the transition
 * between game states and sets the jump state when the game is in progress.
 */
void jump()
#endif
{
  switch (currentState) {
    case PLAYING:
      currentJump = JUMP;  ///< Sets the jump state if the game is in progress
      break;

    default:
      currentState = PLAYING;  ///< Starts the game if it is not in progress
      tree0 = DISPLAY_X - 1;   ///< Initializes the first tree's position
      spawnTree(tree1, tree0); ///< Spawns the second tree
      spawnTree(tree2, tree1); ///< Spawns the third tree
      spawnTree(tree3, tree2); ///< Spawns the fourth tree
      break;
  }
}
