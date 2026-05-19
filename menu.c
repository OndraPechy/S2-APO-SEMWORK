#include <stdint.h>
#include "menu.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "font_render.h"

// budu mit staticky ukazatel pozice toho knobu a
//static uint8_t green_knob_previous_position;

void showMenu()
{

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
   draw_word("1 PLAYER", one_player_text_X, one_player_text_Y, color, scale_buttons);
   color = (cursor == TWO_PLAYERS_CHOICE) ? 255 : 65535;
   draw_word("2 PLAYERS", two_players_text_X, two_players_text_Y, color, scale_buttons);
   color = (cursor == MM_EXIT_CHOICE) ? 255 : 65535;
   draw_word("EXIT", exit_text_X, exit_text_Y, color, scale_buttons);
}

void draw_one_player_menu()
{

}

void draw_two_players_menu()
{

}

void draw_pause_menu()
{

}

void draw_end_menu()
{

}
