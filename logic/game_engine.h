#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <stdbool.h>
#include "menu_logic.h"

typedef enum{ NOT_PLAYING, PLAYING, PAUSED, FINISHED} game_state_t;

void start_game_1p(int difficulty, int target_score);
void start_game_2p(int target_score);
void game_tick(int left_delta, int right_delta);
void pause_game(void);
void resume_game(void);
void stop_game(void);
bool is_game_running(void);
winner_t get_winner(void);
int get_score_left(void);
int get_score_right(void);

#endif