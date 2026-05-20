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
#include "menu_logic.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "knobs_setup.h"
#include "leds_setup.h"
#include "game_engine.h"


void draw_menu(bool *appRunning);

typedef enum
{
   MENU_SCREEN,
   GAME_SCREEN,
} game_state_t;

int main(int argc, char *argv[])
{
   // vytvorim si adresy
   unsigned char *parlcd_mem_base, *mem_base;
   // dostanu adresu zacatku modulu displeje
   parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
   if (parlcd_mem_base == NULL)
      exit(1);

   // a taky adresu zactku ostatnich periferii
   mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
   if (mem_base == NULL) {
      exit(1);
   }

   // taky si vytvorim framebuffer o velikosti displeje do ktereho se to pak
   // bude vsechno psat
   frame_buffer = (unsigned short *)malloc(320 * 480 * sizeof(unsigned short));

   // nainicializuju displej (tohle ten display jakoby ozivy)
   parlcd_hx8357_init(parlcd_mem_base);
   // delay urcite budu pouzivat abych neuvaril display, vyuziva se na to nejaky
   // special struct
   /*
   struct timespec loop_delay;
   loop_delay.tv_sec = 0;
   // je to v nanosekundach a timto jsem z toho udelal 16 milisekund coz je
   // zhruba 60FPS
   loop_delay.tv_nsec = 16 * 1000 * 1000;
   */

   bool appRunning = true;
   setup_knobs(mem_base);
   setup_leds(mem_base);
   reset_values();
   game_state_t state = MENU_SCREEN;
   bool was_playing = false;

   while (appRunning) {
      if (is_game_running()) {
         state = GAME_SCREEN;
      }
      if (state == MENU_SCREEN) {
         draw_menu(&appRunning);
      } else {
         
         for (int index = 0; index < 320 * 480; index++) {
            frame_buffer[index] = 0u;
         }
         check_knobs();
         check_rgb_timer();
         check_rgb_lightening();

         int left_delta = 0;   // red knob = levá pálka
         int right_delta = 0;  // blue knob = pravá pálka

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
            state = MENU_SCREEN;
         }
         update_green_knob_pressed();
         game_tick(left_delta, right_delta);

         if (!is_game_running() && was_playing) {
            state = MENU_SCREEN;
         }
         was_playing = is_game_running();
      }

      // timto parlcd write commandem s tim 0x2c coz je konkretni cislo
      // znamenajici MemoryWrite vlastne displeji reknu, ze ted mu zacnu posilat
      // barvy, at si nastavi kurzor nahoru
      parlcd_write_cmd(parlcd_mem_base, 0x2c);
      for (int index = 0; index < 320 * 480; index++) {
         // timto mu reknu at pro kazdy index vykresli to co je aktualne ve
         // frame bufferu
         parlcd_write_data(parlcd_mem_base, frame_buffer[index]);
      }

      // tenhle nanosleep uspi ten loop na ten nas cas
      //clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
   }
   reset_leds();

   // na konci loopu to cele naplnim cernou
   parlcd_write_cmd(parlcd_mem_base, 0x2c);
   for (int index = 0; index < 320 * 480; index++) {
      parlcd_write_data(parlcd_mem_base, 65535);
   }
   return 0;
}

void draw_menu(bool *appRunning)
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
         increment_cursor();
         update_green_knob();
      } else if (green_knob_moved_down()) {
         decrement_cursor();
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
         make_menu_action(appRunning);
      }

      showMenu();
      update_green_knob_pressed();
}
