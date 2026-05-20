#ifndef PADDLE_H
#define PADDLE_H
#define WALL_OFFSET 15 //Change the distence of paddle and sides
#include <stdbool.h>

typedef struct{
    double y;  //x is done with defined offset
    double height;
    double width;
    bool left;
} paddle_t;

void draw_paddle(paddle_t* paddle, unsigned short int color);
void update_paddle(paddle_t* paddle, int change_y);

#endif