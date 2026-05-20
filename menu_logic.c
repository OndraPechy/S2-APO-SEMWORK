#include "menu_logic.h"
#include "config.h"
#include "font_render.h"
#include "menu_graphics.h"
#include <stdbool.h>
#include <stdio.h>

static int cursor = 0;
static int state = 0;
static int score_to_play = 1;
static int difficulty = NONE_DIFFICULTY_CHOSEN;

void showMenu()
{
   if (state == MAIN_MENU) {
      draw_main_menu(cursor);
   } else if (state == ONE_PLAYER_MENU) {
      draw_one_player_menu(cursor, get_score_string(score_to_play),
                           get_difficulty_string(difficulty),
                           get_difficulty_colour(), score_to_play);
   } else if (state == TWO_PLAYERS_MENU) {
      draw_two_players_menu(cursor, get_score_string(score_to_play),
                            score_to_play);
   } else if (state == PAUSE_MENU) {
      draw_pause_menu(cursor);
   } else if (state == END_MENU) {
      // TO BE CHANGED TO THE CORRECT WINNER
      draw_end_menu(cursor, get_winner_string(BLUE_PLAYER), BLUE_PLAYER);
   } else {
      draw_word("ERROR OCCURED", 100, 100, 21000, 5);
   }
}

int get_menu_options_count(int current_state)
{
   if (current_state == PAUSE_MENU || current_state == END_MENU ||
       current_state == TWO_PLAYERS_MENU) {
      return 2;
   } else if (current_state == ONE_PLAYER_MENU) {
      return 5;
   } else {
      return 3;
   }
}

void increment_cursor()
{
   int limit = get_menu_options_count(state);
   if (limit > 0) {
      cursor = (cursor + 1) % limit;
   }
}

void decrement_cursor()
{
   int limit = get_menu_options_count(state);
   if (limit > 0) {
      cursor = (cursor - 1 + limit) % limit;
   }
}

void increment_score()
{
   if (score_to_play < MAX_SCORE) {
      ++score_to_play;
   }
}

void decrement_score()
{
   if (score_to_play > MIN_SCORE) {
      --score_to_play;
   }
}

void make_menu_action(bool *appRunning)
{
   switch (state) {

      case MAIN_MENU:
         if (cursor == ONE_PLAYER_CHOICE_BUTTON) {
            state = ONE_PLAYER_MENU;
            reset_values();
         } else if (cursor == TWO_PLAYERS_CHOICE_BUTTON) {
            state = TWO_PLAYERS_MENU;
            reset_values();
         } else if (cursor == MM_EXIT_CHOICE_BUTTON) {
            *appRunning = false;
         }
         break;

      case ONE_PLAYER_MENU:
         if (cursor == EASY_DIFFICULTY_BUTTON) {
            difficulty = EASY_DIFFICULTY_CHOSEN;
         } else if (cursor == MEDIUM_DIFFICULTY_BUTTON) {
            difficulty = MEDIUM_DIFFICULTY_CHOSEN;
         } else if (cursor == HARD_DIFFICULTY_BUTTON) {
            difficulty = HARD_DIFFICULTY_CHOSEN;
         } else if (cursor == GO_BACK_1_PLAYER_BUTTON) {
            state = MAIN_MENU;
            reset_values();
         } else if (cursor == START_GAME_1_PLAYER_BUTTON) {
            // TO BE CHANGED TO START THE GAME
            state = PAUSE_MENU;
            reset_values();
         }
         break;

      case TWO_PLAYERS_MENU:
         if (cursor == GO_BACK_2_PLAYERS_BUTTON) {
            state = MAIN_MENU;
            reset_values();
         } else if (cursor == START_GAME_2_PLAYERS_BUTTON) {
            // TO BE CHANGED TO START THE GAME
            state = PAUSE_MENU;
            reset_values();
         }
         break;

      case PAUSE_MENU:
         if (cursor == RESUME_CHOICE_BUTTON) {
            // TO BE CHANGED TO RESUME THE GAME
            state = END_MENU;
            reset_values();
         } else {
            state = MAIN_MENU;
            reset_values();
         }
         break;

      case END_MENU:
         if (cursor == RETURN_TO_MENU_CHOICE_BUTTON) {
            state = MAIN_MENU;
            reset_values();
         } else {
            *appRunning = false;
         }
         break;
   }
}

void reset_values()
{
   cursor = 0;
   score_to_play = 1;
   difficulty = NONE_DIFFICULTY_CHOSEN;
}

const char *get_difficulty_string(int difficulty)
{
   // Klíčové slovo 'static' zajistí, že buffer v paměti nezanikne po skončení
   // funkce
   static char output_buffer[50];
   const char *diff_text;

   switch (difficulty) {
      case 0:
         diff_text = "NONE";
         break;
      case 1:
         diff_text = "EASY";
         break;
      case 2:
         diff_text = "MEDIUM";
         break;
      case 3:
         diff_text = "HARD";
         break;
      default:
         diff_text = "NONE";
         break;
   }

   // Složíme string do statického bufferu
   snprintf(output_buffer, sizeof(output_buffer), "DIFFICULTY CHOSEN: %s",
            diff_text);

   // Vrátíme ukazatel na tento buffer
   return output_buffer;
}

const char *get_score_string(int score)
{
   static char score_buffer[30];
   snprintf(score_buffer, sizeof(score_buffer), "SCORE TO PLAY: %d", score);

   return score_buffer;
}

const char *get_winner_string(int winner)
{

   if (winner == BLUE_PLAYER) {
      return "WINNER: BLUE PLAYER";
   } else if (winner == RED_PLAYER) {
      return "WINNER: RED PLAYER";
   } else {
      return "WINNER: NONE (ERROR)";
   }
}

int get_difficulty_colour()
{
   if (difficulty == EASY_DIFFICULTY_CHOSEN) {
      return GREEN;
   } else if (difficulty == MEDIUM_DIFFICULTY_CHOSEN) {
      return YELLOW;
   } else if (difficulty == HARD_DIFFICULTY_CHOSEN) {
      return RED;
   } else {
      return WHITE;
   }
}
