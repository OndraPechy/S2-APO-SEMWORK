#ifndef MENU_LOGIC_H
#define MENU_LOGIC_H

// im using an enum as states because there will be a while loop that will look
// at a state of a menu each time
typedef enum {
    MAIN_MENU,
    ONE_PLAYER_MENU,
    TWO_PLAYERS_MENU,
    PAUSE_MENU,
    END_MENU
} menu_state_t;

typedef enum
{
   NONE_DIFFICULTY_CHOSEN,
   EASY_DIFFICULTY_CHOSEN,
   MEDIUM_DIFFICULTY_CHOSEN,
   HARD_DIFFICULTY_CHOSEN,
} one_player_difficulty_t;

void showMenu();
int get_menu_options_count(int current_state);
void increment_cursor();
void decrement_cursor();
void make_menu_action(bool *appRunning);
void reset_values();
const char* get_difficulty_string(int difficulty);
const char* get_score_string(int score);

#endif /* MENU_LOGIC_H */
