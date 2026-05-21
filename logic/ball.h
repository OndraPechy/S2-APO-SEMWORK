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

/**
 * @brief Represents the ball with position, velocity and size.
 */
typedef struct ball_s {
    double x;
    double y;
    double change_x;
    double change_y;
    double size;
} ball_t;

/**
 * @brief Result of a single ball update.
 *
 * RALLY        - ball is still in play
 * SCORES_LEFT  - left player scored (ball passed the right wall)
 * SCORES_RIGHT - right player scored (ball passed the left wall)
 */
typedef enum{ RALLY, SCORES_LEFT, SCORES_RIGHT } state_t;

/**
 * @brief Advances the ball by one tick.
 *
 * Moves the ball, handles wall reflections, paddle collisions
 * and detects goals.
 *
 * @param ball    Pointer to the ball.
 * @param left_p  Pointer to the left paddle.
 * @param right_p Pointer to the right paddle.
 * @return State after the update: RALLY, SCORES_LEFT or SCORES_RIGHT.
 */
state_t update_ball(ball_t* ball, paddle_t* left_p, paddle_t* right_p);

/**
 * @brief Checks rectangular overlap between the ball and a paddle.
 *
 * @param ball   Pointer to the ball.
 * @param paddle Pointer to the paddle.
 * @return true if the ball overlaps the paddle, false otherwise.
 */
bool collision_b_p(ball_t* ball, paddle_t* paddle);

/**
 * @brief Reflects the ball off a paddle.
 *
 * Inverts horizontal velocity, sets new vertical velocity based on
 * where the ball hit the paddle (offset from paddle center), applies
 * the speed multiplier and nudges the ball out of the paddle to
 * prevent it from getting stuck.
 *
 * @param ball   Pointer to the ball.
 * @param paddle Pointer to the paddle that was hit.
 */
void bounce(ball_t* ball, paddle_t* paddle);

/**
 * @brief Resets the ball to the center with a random direction.
 *
 * @param ball Pointer to the ball.
 */
void reset_ball(ball_t* ball);

#endif
