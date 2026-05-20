#ifndef PADDLE_H
#define PADDLE_H
#define WALL_OFFSET 15 // the distence between paddles and walls
#define EASY_BOT_SPEED 2
#define MEDIUM_BOT_SPEED 4
#define HARD_BOT_SPEED 6

#include <stdbool.h>

// ZMĚNA: Přidána dopředná deklarace (říká kompilátoru, že typ ball_t existuje)
typedef struct ball_s ball_t;

typedef struct
{
   double y; // x is done with defined offset
   double height;
   double width;
   bool left;
} paddle_t;

void draw_paddle(paddle_t *paddle, unsigned short int color);
void update_paddle(paddle_t *paddle, int change_y);
void update_bot_paddle(paddle_t *paddle, ball_t *ball, int speed);

#endif
