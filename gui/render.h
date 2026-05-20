#ifndef RENDER_H
#define RENDER_H

#define WHITE 0xFFFF
#define RED 0xF800
#define BLUE 0x001F

#include "ball.h"
#include "paddle.h"

void render_game(ball_t *ball, paddle_t *left_p, paddle_t *right_p);

#endif
