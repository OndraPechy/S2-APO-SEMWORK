#include <stdbool.h>
#ifndef MENU_LOGIC_H
#define MENU_LOGIC_H

// im using an enum as states because there will be a while loop that will look
// at a state of a menu each time
typedef enum
{
   MAIN_MENU,
   ONE_PLAYER_MENU,
   TWO_PLAYERS_MENU,
   PAUSE_MENU,
   END_MENU,
   GAME_SCREEN
} app_state_t;

typedef enum
{
   NONE_DIFFICULTY_CHOSEN,
   EASY_DIFFICULTY_CHOSEN,
   MEDIUM_DIFFICULTY_CHOSEN,
   HARD_DIFFICULTY_CHOSEN,
} one_player_difficulty_t;

typedef enum
{
   RED_PLAYER,
   BLUE_PLAYER,
} winner_t;






void showMenu(app_state_t state);
int get_menu_options_count(int current_state);
void increment_cursor(app_state_t state);
void decrement_cursor(app_state_t state);
void increment_score();
void decrement_score();
void make_menu_action(bool *appRunning, app_state_t *state);
void reset_values();
const char *get_difficulty_string(int difficulty);
const char *get_score_string(int score);
const char *get_winner_string(int winner);
int get_difficulty_colour();

#endif /* MENU_LOGIC_H */
