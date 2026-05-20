#ifndef BALL_H
#define BALL_H

#define KICK_MULT 0.15
#define MAX_CHANGE_Y 5.0
#define CENTER_X 240.0
#define CENTER_Y 160.0
#define INIT_SPEED 3.0

#include <stdlib.h>
#include "paddle.h"

typedef struct{
    double x;
    double y;
    double change_x;
    double change_y;
    double size;
} ball_t;

typedef enum{ RALLY, SCORE_LEFT, SCORE_RIGHT } state_t;
state_t update_ball(ball_t* ball);
bool collision_b_p(ball_t* ball, paddle_t* paddle);
void bounce(ball_t* ball, paddle_t* paddle);
void reset_ball(ball_t* ball);

#endif