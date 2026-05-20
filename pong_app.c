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
/*
#include "ball.h"
#include "paddle.h"
#include "render.h"
*/

// TO BE MOVED
#define RED_KNOB_PRESSED_SHIFT 26
#define GREEN_KNOB_PRESSED_MASK 0x02000000
#define GREEN_KNOB_PRESSED_SHIFT 25
#define BLUE_KNOB_PRESSED_SHIFT 24
#define RED_KNOB_MASK 0x00FF0000
#define RED_KNOB_SHIFT 16
#define GREEN_KNOB_MASK 0x0000FF00
#define GREEN_KNOB_SHIFT 8
#define BLUE_KNOB_MASK 0x000000FF
#define BLUE_KNOB_SHIFT 0
#define KNOB_MOVEMENT_DIVIDER 4
char get_knobs_value(int mask, int shift, uint32_t *knob_mem_base);
static uint8_t green_knob_previous_position;
static uint8_t green_knob_pressed_prev;
// -----------

enum currentAppState
{
   MENU_SCREEN,
   GAME_SCREEN,
};

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

   // tim ze pak prictu offset ziskam adresu sveho knobu
   uint32_t *knob_mem = (uint32_t *)(mem_base + SPILED_REG_KNOBS_8BIT_o);

   // taky si vytvorim framebuffer o velikosti displeje do ktereho se to pak
   // bude vsechno psat
   frame_buffer = (unsigned short *)malloc(320 * 480 * sizeof(unsigned short));

   // nainicializuju displej (tohle ten display jakoby ozivy)
   parlcd_hx8357_init(parlcd_mem_base);
   // delay urcite budu pouzivat abych neuvaril display, vyuziva se na to nejaky
   // special struct
   struct timespec loop_delay;
   loop_delay.tv_sec = 0;
   // je to v nanosekundach a timto jsem z toho udelal 16 milisekund coz je
   // zhruba 60FPS
   loop_delay.tv_nsec = 16 * 1000 * 1000;

   green_knob_previous_position =
       get_knobs_value(GREEN_KNOB_MASK, GREEN_KNOB_SHIFT, knob_mem);
   green_knob_pressed_prev = get_knobs_value(
       GREEN_KNOB_PRESSED_MASK, GREEN_KNOB_PRESSED_SHIFT, knob_mem);

   bool appRunning = true;

   while (appRunning) {
      // naplnim cely ten buffer jednim cislem, aby se vykreslila jedna barva
      for (int index = 0; index < 320 * 480; index++) {
         // to u tady znamena ze ta 0 je unsigned
         frame_buffer[index] = 0u;
      }

      uint8_t green_knob_pos =
          get_knobs_value(BLUE_KNOB_MASK, BLUE_KNOB_SHIFT, knob_mem);
      // spoctu jaky je rozdil mezi aktualni a predeslou pozici knobu
      int8_t diff_green =
          (int8_t)(green_knob_pos - green_knob_previous_position);

      if (diff_green <= -KNOB_MOVEMENT_DIVIDER) {
         // otocenim doprava posunu v menu dolu
         green_knob_previous_position = green_knob_pos;
         increment_cursor();
      } else if (diff_blue >= KNOB_MOVEMENT_DIVIDER) {
         // otocenim diff_green posunu v levo nahoru
         // pricitam 3 aby se modulo nepocitalo se zapornym cislem
         green_knob_previous_position = green_knob_pos;
         decrement_cursor();
      }

      uint8_t green_knob_pressed = get_knobs_value(
          GREEN_KNOB_PRESSED_MASK, GREEN_KNOB_PRESSED_SHIFT, knob_mem);
      if ((green_knob_pressed != 0) && (green_knob_pressed_prev == 0)) {
         make_menu_action(&appRunning);
      }
      green_knob_pressed_prev = green_knob_pressed;

      showMenu();

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
      clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
   }

   // na konci loopu to cele naplnim cernou
   parlcd_write_cmd(parlcd_mem_base, 0x2c);
   for (int index = 0; index < 320 * 480; index++) {
      parlcd_write_data(parlcd_mem_base, 65535);
   }

   return 0;
}

// TO BE MOVED
char get_knobs_value(int mask, int shift, uint32_t *knob_mem_base)
{
   int value = *knob_mem_base;
   value = value & mask;
   return value >> shift;
}
// -----------
