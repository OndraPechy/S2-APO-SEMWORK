#include "paddle.h"
#include "shape_render.h"

void draw_paddle(paddle_t* paddle, unsigned short int color){
    
    int x = paddle->left ? WALL_OFFSET : 479 - WALL_OFFSET;  //TODO magic num
    
    draw_rect(x, paddle->y, paddle->width, paddle->height, color);
}

void update_paddle(paddle_t* paddle, int change_y){
    paddle->y += change_y;
    double half = paddle->height / 2;
    if (paddle->y - half <= 0){
        paddle->y = half;
    } 
    if (paddle->y + half >= 319){
        paddle->y = 319 - half;
    }

}

void update_bot_paddle(paddle_t* paddle, ball_t* ball, int speed){
    int change_y = 0;
    if (ball->y < paddle->y){
        change_y = -speed;
    } else if (ball->y > paddle->y){
        change_y = speed;
    }
    update_paddle(paddle, change_y);
}