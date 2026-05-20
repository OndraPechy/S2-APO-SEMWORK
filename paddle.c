#include "paddle.h"
#include "shape_render.h"

void draw_paddle(paddle_t* paddle, unsigned short int color){
    
    int x = paddle->left ? WALL_OFFSET : 479 - WALL_OFFSET;  //TODO magic num
    
    draw_rect(x, paddle->y, paddle->width, paddle->height, color);
}