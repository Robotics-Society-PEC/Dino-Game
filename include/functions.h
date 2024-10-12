/**
 * @file functions.h
 * @brief Function declarations for game logic and hardware control.
 * 
 * This header file declares the functions used in the game for managing the LCD display,
 * spawning and displaying obstacles (trees), handling the dinosaur's movement, and
 * checking for collisions. It also defines the `jump` function with an architecture-specific
 * implementation for handling interrupts.
 * 
 * @author WittyWizard
 * @date 2024-10-12
 */

#pragma once

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>

/**
 * @brief Initializes the LCD display.
 * 
 * This function sets up the LCD display, configuring it for use in the game.
 */
extern void setupLCD();

/**
 * @brief Spawns a tree at a random position based on a previous tree's location.
 * 
 * @param tree The reference to the tree being spawned.
 * @param tree_previous The reference to the previous tree, ensuring distance constraints.
 */
extern void spawnTree(uint8_t &tree, uint8_t &tree_previous);

/**
 * @brief Displays a tree on the LCD screen.
 * 
 * @param tree The reference to the tree's current position to display on the screen.
 */
extern void displayTree(uint8_t &tree);

/**
 * @brief Displays the dinosaur on the LCD screen.
 */
extern void displaydinosour();

/**
 * @brief Checks for collisions between the dinosaur and a tree.
 * 
 * @param tree The reference to the tree's current position.
 * @return True if a collision is detected, false otherwise.
 */
extern bool collisionCheck(uint8_t &tree);

/**
 * @brief Interrupt Service Routine (ISR) for handling the dinosaur's jump.
 * 
 * This function is architecture-specific. For ESP8266, the `IRAM_ATTR` attribute is
 * required to place the ISR in IRAM. For AVR, a standard function is used.
 */
#if defined(ARDUINO_ARCH_ESP8266)
extern void IRAM_ATTR jump();
#elif defined(ARDUINO_ARCH_AVR)
extern void jump();
#endif

#endif  // FUNCTIONS_H
