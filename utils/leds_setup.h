#ifndef LEDS_SETUP_H
#define LEDS_SETUP_H

/**
 * @brief Initializes memory pointers for the LEDs.
 *
 * @param mem_base Physical memory base pointer for the SPILED peripheral.
 */
void setup_leds(unsigned char *mem_base);

/**
 * @brief Updates the physical state of the RGB LEDs.
 * Lightens the LEDs based on the current state of lightening flags.
 */
void check_rgb_lightening();

/**
 * @brief Handles the timing logic for the RGB LEDs.
 * Decrements the timers for both RGB LEDs if they are currently lit.
 * Turns off the flags once the time limit is reached.
 */
void check_rgb_timer();

/**
 * @brief Lightens the RGB1, sets the active flag to true
 * and resets the associated timer.
 */
void lighten_rgb1();

/**
 * @brief Lightens the RGB2, sets the active flag to true
 * and resets the associated timer.
 */
void lighten_rgb2();

/**
 * @brief Updates the 32-bit LED line to display the current game score.
 * @param p1_score Current Player 1.
 * @param p2_score Current Player 2.
 */
void lighten_led_line(int p1_score, int p2_score);

/**
 * @brief Turns off all LEDs and resets internal states and timers.
 */
void reset_leds();

#endif /*LEDS_SETUP_H*/
