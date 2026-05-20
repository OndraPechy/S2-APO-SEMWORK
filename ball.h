#ifndef BALL_H
#define BALL_H
#include "paddle.h"

typedef struct{
    double x;
    double y;
    double change_x;
    double change_y;
    double size;
} ball_t;

void update_ball(ball_t* ball);
bool collision_b_p(ball_t* ball, paddle_t* paddle);

#endif