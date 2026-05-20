#ifndef BALL_H
#define BALL_H

#define KICK_MULT 0.20
#define MAX_CHANGE_Y 8.0 // how much y can chnge
#define CENTER_X 240.0
#define CENTER_Y 160.0
#define INIT_SPEED 8.0  // how fast will the ball be at start
#define SPEED_MULT 1.05 // multiplicate the speed

#include "paddle.h"
#include <stdlib.h>

typedef struct ball_s
{
   double x;
   double y;
   double change_x;
   double change_y;
   double size;
} ball_t;

typedef enum
{
   RALLY,
   SCORES_LEFT,
   SCORES_RIGHT
} state_t;
state_t update_ball(ball_t *ball, paddle_t *left_p, paddle_t *right_p);
bool collision_b_p(ball_t *ball, paddle_t *paddle);
void bounce(ball_t *ball, paddle_t *paddle);
void reset_ball(ball_t *ball);

#endif
