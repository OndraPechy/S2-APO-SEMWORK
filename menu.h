#ifndef MENU_H
#define MENU_H

#include <stdint.h>

// im using an enum as states because there will be a while loop that will look
// at a state of a menu each time
typedef enum {
    MAIN_MENU,
    ONE_PLAYER_MENU,
    TWO_PLAYERS_MENU,
    PAUSE_MENU,
    END_MENU
} menu_state_t;

typedef enum {
    ONE_PLAYER_CHOICE,
    TWO_PLAYERS_CHOICE,
    MM_EXIT_CHOICE
} main_menu_cursor_t;

// NASTAVOVANI POCTU BODU SE BUDE DELAT PRES KNOB

typedef enum {
    EASY_DIFFICULTY,
    MEDIUM_DIFFICULTY,
    HARD_DIFFICULTY
} one_player_menu_cursor_t;

typedef enum {
    RESUME_CHOICE,
    LEAVE_GAME_SCREEN_CHOICE
} pause_menu_cursor_t;

typedef enum {
    RETURN_TO_MENU_CHOICE,
    EXIT_CHOICE
} end_menu_cursor_t;


void showMenu(void);

void draw_main_menu(main_menu_cursor_t cursor);
void draw_one_player_menu(one_player_menu_cursor_t cursor);
void draw_two_players_menu();
void draw_pause_menu(pause_menu_cursor_t cursor);
void draw_end_menu(end_menu_cursor_t cursor);
void increment_cursor();
void decrement_cursor();
void increment_state();
void decrement_state();
void change_menu();


#endif /* MENU_H */
