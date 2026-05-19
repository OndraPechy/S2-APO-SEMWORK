#include "menu.h"
#include "font_render.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include <stdint.h>
#include <stdbool.h>

// TO BE DELETED
#include <stdio.h>

// budu mit staticky cursor a ten se mi vzdycky bude menit
static int cursor = 0;
static int state = 0;

void showMenu()
{
   if (state == MAIN_MENU) {
      draw_main_menu(cursor);
   } else if (state == ONE_PLAYER_MENU) {
      draw_one_player_menu(cursor);
   } else if (state == TWO_PLAYERS_MENU) {
      draw_two_players_menu();
   } else if (state == PAUSE_MENU) {
      draw_pause_menu(cursor);
   } else if (state == END_MENU) {
      draw_end_menu(cursor);
   } else {
      draw_word("ERROR OCCURED", 100, 100, 21000, 5);
   }
}

void draw_main_menu(main_menu_cursor_t cursor)
{
   int scale_headline = 5;
   int scale_buttons = 3;
   int pong_x = 140;
   int pong_Y = 10;
   int one_player_text_X = 140;
   int one_player_text_Y = 120;
   int two_players_text_X = 125;
   int two_players_text_Y = 180;
   int exit_text_X = 190;
   int exit_text_Y = 240;
   int color = 65535;
   draw_word("PONG", pong_x, pong_Y, color, scale_headline);
   color = (cursor == ONE_PLAYER_CHOICE) ? 255 : 65535;
   draw_word("1 PLAYER", one_player_text_X, one_player_text_Y, color,
             scale_buttons);
   color = (cursor == TWO_PLAYERS_CHOICE) ? 255 : 65535;
   draw_word("2 PLAYERS", two_players_text_X, two_players_text_Y, color,
             scale_buttons);
   color = (cursor == MM_EXIT_CHOICE) ? 255 : 65535;
   draw_word("EXIT", exit_text_X, exit_text_Y, color, scale_buttons);
}

void draw_one_player_menu(one_player_menu_cursor_t cursor)
{
   int scale_headline = 5;
   int scale_buttons = 3;
   int pong_x = 140;
   int pong_Y = 10;
   int one_player_text_X = 140;
   int one_player_text_Y = 120;
   int two_players_text_X = 125;
   int two_players_text_Y = 180;
   int exit_text_X = 190;
   int exit_text_Y = 240;
   int color = 65535;
   draw_word("10", pong_x, pong_Y, color, scale_headline);
   color = (cursor == EASY_DIFFICULTY) ? 255 : 65535;
   draw_word("EASY", one_player_text_X, one_player_text_Y, color,
             scale_buttons);
   color = (cursor == MEDIUM_DIFFICULTY) ? 255 : 65535;
   draw_word("MEDIUM", two_players_text_X, two_players_text_Y, color,
             scale_buttons);
   color = (cursor == HARD_DIFFICULTY) ? 255 : 65535;
   draw_word("HARD", exit_text_X, exit_text_Y, color, scale_buttons);
   color = (cursor == GO_BACK_1_PLAYER) ? 255 : 65535;
   draw_word("GO BACK", exit_text_X, exit_text_Y, color, scale_buttons);
}

void draw_two_players_menu()
{
   int scale_headline = 5;
   int pong_x = 140;
   int pong_Y = 10;
   int color = 65535;
   draw_word("10", pong_x, pong_Y, color, scale_headline);
   color = (cursor == GO_BACK_2_PLAYERS) ? 255 : 65535;
   draw_word("GO BACK", pong_x, pong_Y, color, scale_headline);
}

void draw_pause_menu(pause_menu_cursor_t cursor)
{
   int scale_headline = 5;
   int scale_buttons = 3;
   int pong_x = 140;
   int pong_Y = 10;
   int one_player_text_X = 140;
   int one_player_text_Y = 120;
   int two_players_text_X = 125;
   int two_players_text_Y = 180;
   int color = 65535;
   draw_word("10", pong_x, pong_Y, color, scale_headline);
   color = (cursor == RESUME_CHOICE) ? 255 : 65535;
   draw_word("RESUME", one_player_text_X, one_player_text_Y, color,
             scale_buttons);
   color = (cursor == LEAVE_GAME_SCREEN_CHOICE) ? 255 : 65535;
   draw_word("EXIT", two_players_text_X, two_players_text_Y, color,
             scale_buttons);
}

void draw_end_menu(end_menu_cursor_t cursor)
{
   int scale_headline = 5;
   int scale_buttons = 3;
   int pong_x = 140;
   int pong_Y = 10;
   int one_player_text_X = 140;
   int one_player_text_Y = 120;
   int two_players_text_X = 125;
   int two_players_text_Y = 180;
   int color = 65535;
   draw_word("FINISHED", pong_x, pong_Y, color, scale_headline);
   color = (cursor == RETURN_TO_MENU_CHOICE) ? 255 : 65535;
   draw_word("GOT TO MENU", one_player_text_X, one_player_text_Y, color,
             scale_buttons);
   color = (cursor == EXIT_CHOICE) ? 255 : 65535;
   draw_word("EXIT", two_players_text_X, two_players_text_Y, color,
             scale_buttons);
}

int get_menu_options_count(int current_state)
{
   if (current_state == PAUSE_MENU || current_state == END_MENU) {
      return 2;
   } else if (current_state == TWO_PLAYERS_MENU) {
      return 1;
   } else if (current_state == ONE_PLAYER_MENU) {
      return 4;
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

void change_menu(bool *appRunning)
{
   switch (state) {
      case MAIN_MENU:
         if (cursor == ONE_PLAYER_CHOICE) {
            state = ONE_PLAYER_MENU;
         } else if (cursor == TWO_PLAYERS_CHOICE) {
            state = TWO_PLAYERS_MENU;
         } else if (cursor == MM_EXIT_CHOICE) {
            *appRunning = false;
         }
         break;
      case ONE_PLAYER_MENU:
         if (cursor == EASY_DIFFICULTY) {
            printf("EASY CHOSEN");
         } else if (cursor == MEDIUM_DIFFICULTY) {
            printf("MEDIUM CHOSEN");
         } else if (cursor == HARD_DIFFICULTY) {
            printf("HARD CHOSEN");
         } else if (cursor == GO_BACK_1_PLAYER) {
            state = MAIN_MENU;
         }
         break;
      case TWO_PLAYERS_MENU:
         if (cursor == GO_BACK_2_PLAYERS) {
            state = MAIN_MENU;
         }
      case PAUSE_MENU:
         if (cursor == RESUME_CHOICE) {
            printf("SHALL RETURN TO THE GAME");
         } else {
            state = MAIN_MENU;
         }
         break;
      case END_MENU:
         if (cursor == RETURN_TO_MENU_CHOICE) {
            state = MAIN_MENU;
         } else {
            *appRunning = false;
         }
         break;
   }
   cursor = 0;
}
