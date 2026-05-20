#include "ball.h"

state_t update_ball(ball_t* ball, paddle_t* left_p, paddle_t* right_p){
    ball->x += ball->change_x;
    ball->y += ball->change_y;
    if (ball->y - ball->size / 2 <= 0 || ball->y + ball->size / 2 >= 319){
        ball->change_y = -ball->change_y;
    }
    if (collision_b_p(ball, left_p)){
        bounce(ball, left_p);
        
    } else if(collision_b_p(ball, right_p)){
       bounce(ball, right_p);
    }
    if (ball->x <= 0){
        reset_ball(ball);
        return SCORE_RIGHT;
    } else if (ball->x >= 479){
        reset_ball(ball);
        return SCORE_LEFT;
    } else {
        return RALLY;
    }
}

bool collision_b_p(ball_t* ball, paddle_t* paddle){
    int p_x = paddle->left ? WALL_OFFSET : 479 - WALL_OFFSET;
    double b_half = ball->size / 2;
    double p_half_x = paddle->width / 2;
    double p_half_y = paddle->height / 2;
    
    return(ball->x - b_half <= p_x + p_half_x 
        && ball->x + b_half >= p_x - p_half_x
        && ball->y - b_half <= paddle->y + p_half_y
        && ball->y + b_half >= paddle->y - p_half_y);
}

void bounce(ball_t* ball, paddle_t* paddle){
    ball->change_x = -ball->change_x;
    double diff = ball->y - paddle->y;
    ball->change_y = diff * KICK_MULT;
    if (ball->change_y >= MAX_CHANGE_Y){
        ball->change_y = MAX_CHANGE_Y;
    }
    if(ball->change_y <= -MAX_CHANGE_Y){
        ball->change_y = -MAX_CHANGE_Y;
    }
}

void reset_ball(ball_t* ball){
    ball->x = CENTER_X;
    ball->y = CENTER_Y;
    ball->change_x = (rand() % 2 == 0) ? 3.0 : -3.0;
    ball->change_y = ((rand() % 41) - 20) / 10.0; // -2.0 to 2.0
}