/**
 * @file variables.cpp
 * @brief Global variable definitions for the game.
 * 
 * This file contains the definitions of global variables used in the game. These variables 
 * include the LCD object, custom character bitmaps, tree positions, score tracking, and 
 * the current game state.
 * 
 * Author: [Your Name]
 * Date: 2024-10-12
 */

#include "variables.h"
#include "definitions.h"

#ifdef I2C_LCD
/**
 * @brief Global instance of the LiquidCrystal_I2C class for controlling an I2C LCD.
 */
LiquidCrystal_I2C lcd(0x27, 16, 2);
#else
/**
 * @brief Global instance of the LiquidCrystal class for controlling a parallel LCD.
 */
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
#endif

/**
 * @brief Custom character bitmap for the tree.
 * 
 * The `tree` character is displayed as an obstacle in the game. The 8-byte array
 * defines the custom character's pixels in a 5x8 grid.
 */
const char tree[8] = {0B00100, 0B00101, 0B00101, 0B10101,
                      0B10110, 0B01100, 0B00100, 0B00100};

/**
 * @brief Custom character bitmap for the left-facing dinosaur.
 * 
 * The `dinol` character represents the dinosaur facing left, used to show movement.
 */
const char dinol[8] = {0B00111, 0B00100, 0B00111, 0B00100,
                       0B00100, 0B01100, 0B10010, 0B10000};

/**
 * @brief Custom character bitmap for the right-facing dinosaur.
 * 
 * The `dinor` character represents the dinosaur facing right, used to show movement.
 */
const char dinor[8] = {0B00111, 0B00100, 0B00111, 0B00100,
                       0B00100, 0B01100, 0B10010, 0B00010};

/**
 * @brief Current position of the first tree on the display.
 */
uint8_t tree0 = 0;

/**
 * @brief Current position of the second tree on the display.
 */
uint8_t tree1 = 0;

/**
 * @brief Current position of the third tree on the display.
 */
uint8_t tree2 = 0;

/**
 * @brief Current position of the fourth tree on the display.
 */
uint8_t tree3 = 0;

/**
 * @brief Position where the collision occurred (if any).
 */
uint8_t collision_tree = 0;

/**
 * @brief The current score of the game.
 */
int score = 0;

/**
 * @brief The highest score achieved so far.
 */
int high_score = 0;

/**
 * @brief Current motion state of the dinosaur (left or right).
 */
Motion currentMotion = LEFT;

/**
 * @brief Current state of the game (e.g., first start, playing, game over, idle).
 */
GameState currentState = FIRST_START;

/**
 * @brief Current jump state of the dinosaur (e.g., jumping, did jump, no jump).
 */
Jump currentJump = NO_JUMP;
