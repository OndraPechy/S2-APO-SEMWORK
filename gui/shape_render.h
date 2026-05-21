#ifndef SHAPE_RENDER_H
#define SHAPE_RENDER_H

#include "font_render.h"

/**
 * @brief Draws a filled rectangle centered at (x, y).
 *
 * Coordinates refer to the center of the rectangle, not the corner.
 * The rectangle is written directly into the global framebuffer.
 *
 * @param x      Horizontal position of the rectangle center.
 * @param y      Vertical position of the rectangle center.
 * @param width  Width of the rectangle in pixels.
 * @param height Height of the rectangle in pixels.
 * @param color  RGB565 color value.
 */
void draw_rect(double x, double y, double width, double height, unsigned short int color);

#endif
