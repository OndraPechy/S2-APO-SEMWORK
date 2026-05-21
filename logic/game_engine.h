#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <stdbool.h>
#include "menu_logic.h" /* for winner_t */

/**
 * @brief Overall state of the game engine.
 *
 * NOT_PLAYING - no active game
 * PLAYING     - game is running, ticks advance the game state
 * PAUSED      - game is paused, ticks are ignored
 * FINISHED    - one of the players reached the target score
 */
typedef enum{ NOT_PLAYING, PLAYING, PAUSED, FINISHED} game_state_t;

/**
 * @brief Starts a new 1-player game (player vs AI).
 *
 * The left paddle is controlled by the AI, the right paddle by the player.
 *
 * @param difficulty   AI difficulty (1 = easy, 2 = medium, other = hard).
 * @param target_score Score required to win.
 */
void start_game_1p(int difficulty, int target_score);

/**
 * @brief Starts a new 2-player game.
 *
 * @param target_score Score required to win.
 */
void start_game_2p(int target_score);

/**
 * @brief Advances the game by one tick.
 *
 * Updates paddles, ball, handles goals, end-of-game detection
 * and renders the scene. Has no effect if the game is not in
 * the PLAYING state.
 *
 * @param left_delta  Vertical movement of the left paddle
 * @param right_delta Vertical movement of the right paddle.
 */
void game_tick(int left_delta, int right_delta);

/** @brief Pauses the running game. */
void pause_game(void);

/** @brief Resumes a paused game. */
void resume_game(void);

/** @brief Stops the game completely. */
void stop_game(void);

/**
 * @brief Tells whether the game is actively running.
 * @return true if state is PLAYING, false otherwise (including PAUSED).
 */
bool is_game_running(void);

/**
 * @brief Returns the winner of the last finished game.
 *        Valid only after the game state = FINISHED.
 */
winner_t get_winner(void);

/** @brief Returns the current score of the left player. */
int get_score_left(void);

/** @brief Returns the current score of the right player. */
int get_score_right(void);

#endif
