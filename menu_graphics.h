#ifndef MENU_GRAPHICS_H
#define MENU_GRAPHICS_H

typedef enum
{
   ONE_PLAYER_CHOICE_BUTTON,
   TWO_PLAYERS_CHOICE_BUTTON,
   MM_EXIT_CHOICE_BUTTON
} main_menu_cursor_t;

// NASTAVOVANI POCTU BODU SE BUDE DELAT PRES KNOB

typedef enum
{
   EASY_DIFFICULTY_BUTTON,
   MEDIUM_DIFFICULTY_BUTTON,
   HARD_DIFFICULTY_BUTTON,
   GO_BACK_1_PLAYER_BUTTON,
   START_GAME_1_PLAYER_BUTTON
} one_player_menu_cursor_t;

typedef enum
{
   GO_BACK_2_PLAYERS_BUTTON,
   START_GAME_2_PLAYERS_BUTTON
} two_players_menu_cursor_t;

typedef enum
{
   RESUME_CHOICE_BUTTON,
   LEAVE_GAME_SCREEN_CHOICE_BUTTON
} pause_menu_cursor_t;

typedef enum
{
   RETURN_TO_MENU_CHOICE_BUTTON,
   EXIT_CHOICE_BUTTON
} end_menu_cursor_t;

void draw_main_menu(main_menu_cursor_t cursor);
void draw_one_player_menu(one_player_menu_cursor_t cursor,
                          const char *score_string,
                          const char *difficulty_string, int difficulty_colour,
                          int score);
void draw_two_players_menu(two_players_menu_cursor_t cursor,
                           const char *score_string, int score);
void draw_pause_menu(pause_menu_cursor_t cursor);
void draw_end_menu(end_menu_cursor_t cursor, const char *winner_string,
                   int winner);
int get_score_color(int multiplier);

#endif /* MENU_GRAPHICS_H */
