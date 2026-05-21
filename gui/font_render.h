#ifndef FONT_RENDER_H
#define FONT_RENDER_H

#include "font_types.h"

/**
 * @brief External reference to the font descriptor used for rendering.
 */
extern font_descriptor_t font_winFreeSystem14x16;

/**
 * @brief Global pointer to the memory allocated for the display frame buffer.
 */
extern unsigned short *frame_buffer;

/**
 * @brief Draws a string of characters onto the screen.
 * Iterates through the provided string and draws each character sequentially.
 * @param word The null-terminated string to be drawn.
 * @param pos_x The starting X coordinate.
 * @param pos_y The starting Y coordinate.
 * @param color The 16-bit color code.
 * @param scale The scaling factor of the text.
 */
void draw_word(const char *word, int pos_x, int pos_y, unsigned short int color,
               int scale);

/**
 * @brief Draws a single character.
 * Extracts the bitmap data for the requested character from the font descriptor
 * and renders it pixel by pixel according to the specified scale.
 * @param letter The character to draw.
 * @param pos_x The starting X coordinate.
 * @param pos_y The starting Y coordinate.
 * @param color The 16-bit color code for the character.
 * @param scale The scaling factor.
 * @return int The total width taken by the drawn character (font width * scale).
 */
int draw_char(char letter, int pos_x, int pos_y, unsigned short int color,
              int scale);

/**
 * @brief Renders a single pixel into the frame buffer.
 * @param x The X coordinate of the pixel.
 * @param y The Y coordinate of the pixel.
 * @param color The 16-bit color code.
 */
void draw_pixel(int x, int y, unsigned short int color);

#endif /* FONT_DRAWER_H */
