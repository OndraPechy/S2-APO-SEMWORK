#include "knobs_setup.h"
#include "mzapo_regs.h"
#include <stdbool.h>
#include <stdint.h>

#define GREEN_KNOB_PRESSED_MASK 0x02000000
#define GREEN_KNOB_PRESSED_SHIFT 25
#define RED_KNOB_MASK 0x00FF0000
#define RED_KNOB_SHIFT 16
#define GREEN_KNOB_MASK 0x0000FF00
#define GREEN_KNOB_SHIFT 8
#define BLUE_KNOB_MASK 0x000000FF
#define BLUE_KNOB_SHIFT 0
#define KNOB_MOVEMENT_DIVIDER 4

static uint8_t green_knob_previous_position;
static uint8_t blue_knob_previous_position;
static uint8_t red_knob_previous_position;

static uint8_t green_knob_now_position;
static uint8_t blue_knob_now_position;
static uint8_t red_knob_now_position;

static uint8_t green_knob_previous_pressed;
static uint8_t green_knob_now_pressed;

static uint32_t *knob_mem;

void setup_knobs(unsigned char *mem_base)
{
   // tim ze pak prictu offset ziskam adresu sveho knobu
   knob_mem = (uint32_t *)(mem_base + SPILED_REG_KNOBS_8BIT_o);

   green_knob_previous_position =
       get_knobs_value(GREEN_KNOB_MASK, GREEN_KNOB_SHIFT, knob_mem);

   blue_knob_previous_position =
       get_knobs_value(BLUE_KNOB_MASK, BLUE_KNOB_SHIFT, knob_mem);

   red_knob_previous_position =
       get_knobs_value(RED_KNOB_MASK, RED_KNOB_SHIFT, knob_mem);

   green_knob_previous_pressed = get_knobs_value(
       GREEN_KNOB_PRESSED_MASK, GREEN_KNOB_PRESSED_SHIFT, knob_mem);
}

void check_knobs()
{
   green_knob_now_position =
       get_knobs_value(GREEN_KNOB_MASK, GREEN_KNOB_SHIFT, knob_mem);

   blue_knob_now_position =
       get_knobs_value(BLUE_KNOB_MASK, BLUE_KNOB_SHIFT, knob_mem);

   red_knob_now_position =
       get_knobs_value(RED_KNOB_MASK, RED_KNOB_SHIFT, knob_mem);

   green_knob_now_pressed = get_knobs_value(GREEN_KNOB_PRESSED_MASK,
                                            GREEN_KNOB_PRESSED_SHIFT, knob_mem);
}

void update_green_knob()
{
   green_knob_previous_position = green_knob_now_position;
}

void update_red_knob()
{
   red_knob_previous_position = red_knob_now_position;
}

void update_blue_knob()
{
   blue_knob_previous_position = blue_knob_now_position;
}

void update_green_knob_pressed()
{
   green_knob_previous_pressed = green_knob_now_pressed;
}

bool green_knob_moved_up()
{
   return ((int8_t)(green_knob_now_position - green_knob_previous_position) <=
           -KNOB_MOVEMENT_DIVIDER);
}

bool green_knob_moved_down()
{
   return ((int8_t)(green_knob_now_position - green_knob_previous_position) >=
           KNOB_MOVEMENT_DIVIDER);
}

bool blue_knob_moved_up()
{
   return ((int8_t)(blue_knob_now_position - blue_knob_previous_position) <=
           -KNOB_MOVEMENT_DIVIDER);
}

bool blue_knob_moved_down()
{
   return ((int8_t)(blue_knob_now_position - blue_knob_previous_position) >=
           KNOB_MOVEMENT_DIVIDER);
}

bool red_knob_moved_up()
{
   return ((int8_t)(red_knob_now_position - red_knob_previous_position) <=
           -KNOB_MOVEMENT_DIVIDER);
}

bool red_knob_moved_down()
{
   return ((int8_t)(red_knob_now_position - red_knob_previous_position) >=
           KNOB_MOVEMENT_DIVIDER);
}

bool is_green_knob_clicked()
{
   return ((green_knob_now_pressed != 0) && (green_knob_previous_pressed == 0));
}

char get_knobs_value(int mask, int shift, uint32_t *knob_mem_base)
{
   int value = *knob_mem_base;
   value = value & mask;
   return value >> shift;
}
