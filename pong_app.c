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

void execute_game_loop(app_state_t *state);
void draw_menu(bool *appRunning, app_state_t *state);

/**
 * @brief Main entry point of the program.
 *
 * Initializes memory mapping for peripherals, allocates the frame buffer,
 * and starts the main application loop.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Return code (0 on successful exit).
 */
int main(int argc, char *argv[])
{
   unsigned char *parlcd_mem_base, *mem_base;
   parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
   if (parlcd_mem_base == NULL)
      exit(1);

   mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
   if (mem_base == NULL)
      exit(1);

   // Allocate buffer for the entire display
   frame_buffer = (unsigned short *)malloc(320 * 480 * sizeof(unsigned short));
   parlcd_hx8357_init(parlcd_mem_base);

   bool appRunning = true;
   setup_knobs(mem_base);
   setup_leds(mem_base);
   reset_values();
   app_state_t state = MAIN_MENU;

   while (appRunning) {
      game_state_t engine_state = get_current_game_state();

      switch (state) {
         case GAME_SCREEN:
            if (engine_state == PAUSED) {
               state = PAUSE_MENU;
            } else if (engine_state == FINISHED) {
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

      if (state == GAME_SCREEN) {
         execute_game_loop(&state);
      } else {
         draw_menu(&appRunning, &state);
      }

      parlcd_write_cmd(parlcd_mem_base, 0x2c);
      for (int index = 0; index < 320 * 480; index++) {
         parlcd_write_data(parlcd_mem_base, frame_buffer[index]);
      }
   }

   // Cleanup and white screen at the end
   reset_leds();
   parlcd_write_cmd(parlcd_mem_base, 0x2c);
   for (int index = 0; index < 320 * 480; index++) {
      parlcd_write_data(parlcd_mem_base, 0xFFFF);
   }
   return 0;
}

/**
 * @brief Handles the logic and rendering during gameplay.
 *
 * Reads inputs from the knobs, calculates paddle movement,
 * and calls the game engine tick.
 *
 * @param state Pointer to the current application state.
 */
void execute_game_loop(app_state_t *state)
{
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
      *state = PAUSE_MENU;
   }

   update_green_knob_pressed();
   game_tick(left_delta, right_delta);
}

/**
 * @brief Handles the logic and rendering of the MENU.
 *
 * Reads inputs from the knobs to navigate the menu.
 *
 * @param appRunning Pointer to the application running flag.
 * @param state Pointer to the current application state.
 */
void draw_menu(bool *appRunning, app_state_t *state)
{
   check_knobs();
   check_rgb_timer();
   check_rgb_lightening();
   for (int index = 0; index < 320 * 480; index++) {
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
