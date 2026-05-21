#include "menu_graphics.h"
#include "config.h"
#include "font_render.h"

static int colour;

void draw_main_menu(main_menu_cursor_t cursor)
{
   draw_word("PONG", MM_PONG_POS_X, MM_PONG_POS_Y, WHITE, HEADLINE_SCALE);
   colour = (cursor == ONE_PLAYER_CHOICE_BUTTON) ? PURPLE : WHITE;
   draw_word("1 PLAYER", MM_ONE_P_POS_X, MM_ONE_P_POS_Y, colour,
             BUTTON_BIGGER_SCALE);
   colour = (cursor == TWO_PLAYERS_CHOICE_BUTTON) ? PURPLE : WHITE;
   draw_word("2 PLAYERS", MM_TWO_P_POS_X, MM_TWO_P_POS_Y, colour,
             BUTTON_BIGGER_SCALE);
   colour = (cursor == MM_EXIT_CHOICE_BUTTON) ? PURPLE : WHITE;
   draw_word("EXIT", MM_EXIT_POS_X, MM_EXIT_POS_Y, colour, BUTTON_BIGGER_SCALE);
}

void draw_one_player_menu(one_player_menu_cursor_t cursor,
                          const char *score_string,
                          const char *difficulty_string, int difficulty_colour,
                          int score)
{
   draw_word("1 PLAYER", OPM_HEADLINE_POS_X, OPM_HEADLINE_POS_Y, WHITE,
             HEADLINE_SCALE);
   draw_word(score_string, OPM_SCORE_POS_X, OPM_SCORE_POS_Y,
             get_score_color(score), INFO_BIGGER_SCALE);
   draw_word(difficulty_string, OPM_DIFFICULTY_POS_X, OPM_DIFFICULTY_POS_Y,
             difficulty_colour, INFO_LOWER_SCALE);

   colour = (cursor == EASY_DIFFICULTY_BUTTON) ? GREEN : WHITE;
   draw_word("EASY", OPM_EASY_POS_X, OPM_EASY_POS_Y, colour,
             BUTTON_LOWER_SCALE);
   colour = (cursor == MEDIUM_DIFFICULTY_BUTTON) ? YELLOW : WHITE;
   draw_word("MEDIUM", OPM_MEDIUM_POS_X, OPM_MEDIUM_POS_Y, colour,
             BUTTON_LOWER_SCALE);
   colour = (cursor == HARD_DIFFICULTY_BUTTON) ? RED : WHITE;
   draw_word("HARD", OPM_HARD_POS_X, OPM_HARD_POS_Y, colour,
             BUTTON_LOWER_SCALE);

   colour = (cursor == GO_BACK_1_PLAYER_BUTTON) ? PURPLE : WHITE;
   draw_word("RETURN", OPM_GO_BACK_POS_X, OPM_GO_BACK_POS_Y, colour,
             BUTTON_BIGGER_SCALE);
   colour = (cursor == START_GAME_1_PLAYER_BUTTON) ? PURPLE : WHITE;
   draw_word("START", OPM_START_POS_X, OPM_START_POS_Y, colour,
             BUTTON_BIGGER_SCALE);
}

void draw_two_players_menu(two_players_menu_cursor_t cursor,
                           const char *score_string, int score)
{
   draw_word("2 PLAYERS", TPM_HEADLINE_POS_X, TPM_HEADLINE_POS_Y, WHITE,
             HEADLINE_SCALE);
   draw_word(score_string, TPM_SCORE_POS_X, TPM_SCORE_POS_Y,
             get_score_color(score), INFO_BIGGER_SCALE);
   colour = (cursor == GO_BACK_2_PLAYERS_BUTTON) ? PURPLE : WHITE;
   draw_word("RETURN", TPM_GO_BACK_POS_X, TPM_GO_BACK_POS_Y, colour,
             BUTTON_BIGGER_SCALE);
   colour = (cursor == START_GAME_2_PLAYERS_BUTTON) ? PURPLE : WHITE;
   draw_word("START", TPM_START_POS_X, TPM_START_POS_Y, colour,
             BUTTON_BIGGER_SCALE);
}

void draw_pause_menu(pause_menu_cursor_t cursor)
{
   draw_word("PAUSED!", PM_PAUSED_POS_X, PM_PAUSED_POS_Y, WHITE,
             HEADLINE_SCALE);
   colour = (cursor == LEAVE_GAME_SCREEN_CHOICE_BUTTON) ? PURPLE : WHITE;
   draw_word("GO TO MENU", PM_MENU_POS_X, PM_MENU_POS_Y, colour,
             BUTTON_BIGGER_SCALE);
   colour = (cursor == RESUME_CHOICE_BUTTON) ? PURPLE : WHITE;
   draw_word("RESUME", PM_RESUME_POS_X, PM_RESUME_POS_Y, colour,
             BUTTON_BIGGER_SCALE);
}

void draw_end_menu(end_menu_cursor_t cursor, const char *winner_string,
                   int winner)
{
   draw_word("FINISHED!", EM_FINISHED_POS_X, EM_FINISHED_POS_Y, WHITE,
             HEADLINE_SCALE);
   colour = (winner == 1) ? BLUE : RED;
   draw_word(winner_string, EM_WINNER_POS_X, EM_WINNER_POS_Y, colour,
             INFO_LOWER_SCALE);

   colour = (cursor == RETURN_TO_MENU_CHOICE_BUTTON) ? PURPLE : WHITE;
   draw_word("GO TO MENU", EM_MENU_POS_X, EM_MENU_POS_Y, colour,
             BUTTON_BIGGER_SCALE);
   colour = (cursor == EXIT_CHOICE_BUTTON) ? PURPLE : WHITE;
   draw_word("EXIT", EM_EXIT_POS_X, EM_EXIT_POS_Y, colour, BUTTON_BIGGER_SCALE);
}

int get_score_color(int multiplier)
{
   int min_b = 31;
   int max_b = 31;

   int min_r = 5;
   int max_r = 25;

   int min_g = 20;
   int max_g = 55;
   int divider = 9;

   int r = (max_r + ((min_r - max_r) * (multiplier - 1) / divider));
   int g = (max_g + ((min_g - max_g) * (multiplier - 1) / divider));
   int b = (max_b + ((min_b - max_b) * (multiplier - 1) / divider));
   return ((r << 11) | (g << 5) | b);
}
