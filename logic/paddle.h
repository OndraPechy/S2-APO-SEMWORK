#ifndef PADDLE_H
#define PADDLE_H
/** Horizontal distance of paddle center from the side of the display. */
#define WALL_OFFSET 15 

/** AI paddle speed per tick on each difficulty. */
#define EASY_BOT_SPEED 2
#define MEDIUM_BOT_SPEED 4
#define HARD_BOT_SPEED 6

#include <stdbool.h>

/* forward declaration to avoid circular include with ball.h */
typedef struct ball_s ball_t;

/**
 * @brief Represents a paddle.
 *
 * The X position is not stored explicitly. It is derived from the
 * 'left' flag and WALL_OFFSET, since paddles never move horizontally.
 */
typedef struct{
    double y;  //x is done with defined offset
    double height;
    double width;
    bool left;
} paddle_t;

/**
 * @brief Draws a paddle into the framebuffer.
 *
 * The paddle is drawn as a filled rectangle. The color is chosen
 * based on the 'left' flag (left = red, right = blue).
 *
 * @param paddle Pointer to the paddle to draw.
 * @param color RGB565 color value.
 */
void draw_paddle(paddle_t* paddle, unsigned short int color);

/**
 * @brief Moves the paddle by a given delta and clamps it to the field.
 *
 * @param paddle Pointer to the paddle.
 * @param change_y  Vertical delta in pixels. Negative = up, positive = down.
 */
void update_paddle(paddle_t* paddle, int change_y);

/**
 * @brief Moves the AI paddle towards the ball's vertical position.
 *
 * @param paddle Pointer to the AI paddle.
 * @param ball   Pointer to the ball.
 * @param speed  Maximum movement per tick (depends on difficulty).
 */
void update_bot_paddle(paddle_t* paddle, ball_t* ball, int speed);

#endif
