/**
 * @file definitions.h
 * @brief Contains definitions and configurations for the game hardware and
 * settings.
 *
 * This file defines constants and configurations specific to the hardware being
 * used, such as pin assignments for the LCD and button. It also includes
 * game-specific constants like display dimensions and game speed.
 *
 * @author WittyWizard
 * @date 2024-10-12
 */

#pragma once

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <Arduino.h>

#ifndef I2C_LCD
/**
 * @brief Pin definitions for non-I2C LCD display.
 */
#define RS 12 ///< Register Select pin for LCD
#define EN 11 ///< Enable pin for LCD
#define D4 7  ///< Data pin D4 for LCD
#define D5 6  ///< Data pin D5 for LCD
#define D6 5  ///< Data pin D6 for LCD
#define D7 4  ///< Data pin D7 for LCD
#endif

/**
 * @brief Button pin definition based on the microcontroller architecture.
 *
 * The button pin is defined differently for ESP8266 and AVR architectures.
 */
#if defined(ARDUINO_ARCH_ESP8266)
#define BTN_PIN 14 ///< Button pin for ESP8266
#elif defined(ARDUINO_ARCH_AVR)
#define BTN_PIN 2 ///< Button pin for AVR
#endif

/**
 * @brief Position of the dinosaur on the display (x-coordinate).
 */
#define DINOSAUR_POSITION 2

/**
 * @brief Minimum and maximum distances between trees on the display.
 */
#define MIN_TREE_DISTANCE 4  ///< Minimum distance between trees
#define MAX_TREE_DISTANCE 12 ///< Maximum distance between trees

/**
 * @brief Display dimensions and row definitions.
 */
#define DISPLAY_X 16     ///< Number of columns on the display
#define DISPLAY_Y 2      ///< Number of rows on the display
#define DISPLAY_BOTTOM 1 ///< Defines the bottom row index of the display
#define DISPLAY_TOP 0    ///< Defines the top row index of the display

/**
 * @brief Game speed definition in milliseconds.
 *
 * This constant controls the speed of the game. Lower values result in faster
 * gameplay.
 */
#define GAME_SPEED 300

#endif // DEFINITIONS_H
