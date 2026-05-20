#ifndef PADDLE_H
#define PADDLE_H
#define WALL_OFFSET 15 //Change the distence of paddle and sides
#include <stdbool.h>

typedef struct{
    double y;  //only y because x is meant to be defined
    double height;
    double width;
    bool left;
} paddle_t;

void draw_paddle(paddle_t* paddle, unsigned short int color);

#endif