#include "ball.h"

/* receives pointer at struct ball_t, and does one tick */

void update_ball(ball_t* ball){
    ball->x += ball->change_x;
    ball->y += ball->change_y;
    if (ball->y - ball->size / 2 <= 0 || ball->y + ball->size / 2 >= 319){
        ball->change_y = -ball->change_y;
    }
}