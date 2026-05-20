/*******************************************************************
  Project PONG main function for MZ_APO board
  designed by Ondrej Pechanec and Filip Marik

  License: MIT
 *******************************************************************/

#define _POSIX_C_SOURCE 200112L

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h> //termios, TCSANOW, ECHO, ICANON
#include <time.h>
#include <unistd.h>

#include "font_render.h"
#include "font_types.h"
#include "game_engine.h"
#include "knobs_setup.h"
#include "leds_setup.h"
#include "menu_logic.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

void draw_menu(bool *appRunning, app_state_t *state);

int main(int argc, char *argv[])
{
   unsigned char *parlcd_mem_base, *mem_base;
   parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
   if (parlcd_mem_base == NULL)
      exit(1);

   mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
   if (mem_base == NULL)
      exit(1);

   frame_buffer = (unsigned short *)malloc(320 * 480 * sizeof(unsigned short));
   parlcd_hx8357_init(parlcd_mem_base);

   bool appRunning = true;
   setup_knobs(mem_base);
   setup_leds(mem_base);
   reset_values();
   app_state_t state = MAIN_MENU;

   while (appRunning) {
      // 1. Zjištění stavu hry z enginu
      game_state_t engine_state = get_current_game_state();

      // 2. Přechody stavového automatu
      switch (state) {
         case GAME_SCREEN:
            if (engine_state == PAUSED) {
               state = PAUSE_MENU;
            }
            else if (engine_state == FINISHED) {
               state = END_MENU;
            }
            break;
         case PAUSE_MENU:
            if (engine_state == PLAYING) {
               state = GAME_SCREEN;
            }
            break;
         default:
            break;
      }

      // 3. Vykreslování a logika
      if (state == GAME_SCREEN) {
         for (int index = 0; index < 320 * 480; index++)
            frame_buffer[index] = 0u;

         check_knobs();
         check_rgb_timer();
         check_rgb_lightening();

         int left_delta = 0;
         int right_delta = 0;

         if (red_knob_moved_up()) {
            left_delta = -PADDLE_KNOB_STEP;
            update_red_knob();
         } else if (red_knob_moved_down()) {
            left_delta = PADDLE_KNOB_STEP;
            update_red_knob();
         }

         if (blue_knob_moved_up()) {
            right_delta = -PADDLE_KNOB_STEP;
            update_blue_knob();
         } else if (blue_knob_moved_down()) {
            right_delta = PADDLE_KNOB_STEP;
            update_blue_knob();
         }

         if (is_green_knob_clicked()) {
            pause_game();
            reset_values();
            state = PAUSE_MENU;
         }

         update_green_knob_pressed();
         game_tick(left_delta, right_delta);
      } else {
         draw_menu(
             &appRunning,
             &state); // Předáváme ukazatel na state pro možnost změny v menu
      }

      // 4. Přenos na displej
      parlcd_write_cmd(parlcd_mem_base, 0x2c);
      for (int index = 0; index < 320 * 480; index++) {
         parlcd_write_data(parlcd_mem_base, frame_buffer[index]);
      }
   }

   reset_leds();
   parlcd_write_cmd(parlcd_mem_base, 0x2c);
   for (int index = 0; index < 320 * 480; index++) {
      parlcd_write_data(parlcd_mem_base, 0xFFFF);
   }
   return 0;
}

void draw_menu(bool *appRunning, app_state_t *state)
{
   check_knobs();
   check_rgb_timer();
   check_rgb_lightening();
   // naplnim cely ten buffer jednim cislem, aby se vykreslila jedna barva
   for (int index = 0; index < 320 * 480; index++) {
      // to u tady znamena ze ta 0 je unsigned
      frame_buffer[index] = 0u;
   }

   if (green_knob_moved_up()) {
      increment_cursor(*state);
      update_green_knob();
   } else if (green_knob_moved_down()) {
      decrement_cursor(*state);
      update_green_knob();
   }

   if (blue_knob_moved_up()) {
      increment_score();
      update_blue_knob();
   } else if (blue_knob_moved_down()) {
      decrement_score();
      update_blue_knob();
   }

   if (is_green_knob_clicked()) {
      make_menu_action(appRunning, state);
   }

   showMenu(*state);
   update_green_knob_pressed();
}
