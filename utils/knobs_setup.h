#include <stdbool.h>
#include <stdint.h>
#ifndef KNOBS_SETUP_H
#define KNOBS_SETUP_H
#define PADDLE_KNOB_STEP 20

/**
 * @brief Initializes memory pointers for the knobs.
 *
 * @param mem_base Physical memory base pointer for the SPILED peripheral.
 */
void setup_knobs(unsigned char *mem_base);

/**
 * @brief Gets the current physical state of all knobs.
 */
void check_knobs();

/**
 * @brief Synchronizes the previous green knob position with the current one.
 */
void update_green_knob();

/**
 * @brief Synchronizes the previous red knob position with the current one.
 */
void update_red_knob();

/**
 * @brief Synchronizes the previous blue knob position with the current one.
 */
void update_blue_knob();

/**
 * @brief Synchronizes the previous green knob pressed state with the current one.
 */
void update_green_knob_pressed();

/**
 * @brief Checks if the green knob was rotated clockwise.
 * @return true if movement happend, false otherwise.
 */
bool green_knob_moved_up();

/**
 * @brief Checks if the green knob was rotated counter-clockwise.
 * @return true if movement happend, false otherwise.
 */
bool green_knob_moved_down();

/**
 * @brief Checks if the blue knob was rotated clockwise.
 * @return true if movement happend, false otherwise.
 */
bool blue_knob_moved_up();

/**
 * @brief Checks if the blue knob was rotated counter-clockwise.
 * @return true if movement happend, false otherwise.
 */
bool blue_knob_moved_down();

/**
 * @brief Checks if the red knob was rotated clockwise.
 * @return true if movement happend, false otherwise.
 */
bool red_knob_moved_up();

/**
 * @brief Checks if the red knob was rotated counter-clockwise.
 * @return true if movement happend, false otherwise.
 */
bool red_knob_moved_down();

/**
 * @brief Checks wheter the green knob was pressed.
 * @return true if the knob was just pressed this tick, false otherwise.
 */
bool is_green_knob_clicked();

/**
 * @brief Extracts a 8-bit value from the 32-bit register.
 *
 * @param mask Mask to isolate the specific knob's data.
 * @param shift Number of bits to shift to get the normalized value.
 * @param knob_mem_base Pointer to the hardware register containing knob states.
 * @return char The isolated 8-bit value (0-255).
 */
char get_knobs_value(int mask, int shift, uint32_t *knob_mem_base);

#endif /*KNOBS_SETUP_H*/
