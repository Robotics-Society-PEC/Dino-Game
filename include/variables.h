/**
 * @file variables.h
 * @brief Global variable declarations for the game.
 *
 * This header file declares the global variables used throughout the game,
 * including the LCD display instance, custom characters, game states, motion
 * states, and jump states. It also defines variables for tracking the positions
 * of trees, the score, and the game's high score.
 *
 * Author: WittyWizard
 * Date: 2024-10-12
 */

#pragma once

#ifndef VARIABLES_H
#define VARIABLES_H

#include <Arduino.h>

#ifdef I2C_LCD
#include <LiquidCrystal_I2C.h>
/**
 * @brief Global instance of the LiquidCrystal_I2C class for I2C-based LCDs.
 */
extern LiquidCrystal_I2C lcd;
#else
#include <LiquidCrystal.h>
/**
 * @brief Global instance of the LiquidCrystal class for parallel-based LCDs.
 */
extern LiquidCrystal lcd;
#endif

/**
 * @brief Enum representing custom characters for the game (tree and dinosaur).
 */
enum CustomChars {
  TREE = 0,  ///< Tree character
  DINOR = 1, ///< Right-facing dinosaur character
  DINOL = 2  ///< Left-facing dinosaur character
};

/**
 * @brief Enum representing the different states of the game.
 */
enum GameState {
  FIRST_START, ///< Game has not started yet
  PLAYING,     ///< Game is currently in progress
  GAME_OVER,   ///< Game has ended (dinosaur collided with tree)
  IDLE         ///< Game is idle, waiting for player to start again
};

/**
 * @brief Enum representing the direction of the dinosaur's movement.
 */
enum Motion {
  LEFT, ///< Dinosaur is facing left
  RIGHT ///< Dinosaur is facing right
};

/**
 * @brief Enum representing the jump state of the dinosaur.
 */
enum Jump {
  JUMP,   ///< Dinosaur is in the middle of a jump
  NO_JUMP ///< Dinosaur is not jumping
};

/**
 * @brief Custom character data for the tree.
 */
extern const char tree[8];

/**
 * @brief Custom character data for the left-facing dinosaur.
 */
extern const char dinol[8];

/**
 * @brief Custom character data for the right-facing dinosaur.
 */
extern const char dinor[8];

/**
 * @brief Current position of the first tree on the display.
 */
extern uint8_t tree0;

/**
 * @brief Current position of the second tree on the display.
 */
extern uint8_t tree1;

/**
 * @brief Current position of the third tree on the display.
 */
extern uint8_t tree2;

/**
 * @brief Current position of the fourth tree on the display.
 */
extern uint8_t tree3;

/**
 * @brief Position where the collision occurred (if any).
 */
extern uint8_t collision_tree;

/**
 * @brief The current score of the game.
 */
extern int score;

/**
 * @brief The highest score achieved so far.
 */
extern int high_score;

/**
 * @brief Current state of the game.
 */
extern GameState currentState;

/**
 * @brief Current motion state of the dinosaur (left or right).
 */
extern Motion currentMotion;

/**
 * @brief Current jump state of the dinosaur.
 */
extern Jump currentJump;

#endif // VARIABLES_H
