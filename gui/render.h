#ifndef RENDER_H
#define RENDER_H

#define WHITE 0xFFFF
#define RED 0xF800
#define BLUE 0x001F

#include "ball.h"
#include "paddle.h"

/**
 * @brief Renders the whole game scene into the framebuffer.
 *
 * Draws the middle dashed line, top and bottom field borders,
 * both paddles (left = red, right = blue) and the ball.
 *
 * @param ball    Pointer to the ball.
 * @param left_p  Pointer to the left paddle.
 * @param right_p Pointer to the right paddle.
 */
void render_game(ball_t* ball, paddle_t* left_p, paddle_t* right_p);

#endif