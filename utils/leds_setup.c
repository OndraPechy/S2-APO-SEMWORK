#include "leds_setup.h"
#include "mzapo_regs.h"
#include <stdbool.h>
#include <stdint.h>

#define RGB_LIGHTENED_TIME 80

static bool shall_lighten_rgb1 = false;
static bool shall_lighten_rgb2 = false;
static int rgb1_timer;
static int rgb2_timer;
static uint32_t *rgb1_mem;
static uint32_t *rgb2_mem;
static uint32_t *led_line_mem;

void setup_leds(unsigned char *mem_base)
{
   rgb1_mem = (uint32_t *)(mem_base + SPILED_REG_LED_RGB1_o);
   rgb2_mem = (uint32_t *)(mem_base + SPILED_REG_LED_RGB2_o);
   led_line_mem = (uint32_t *)(mem_base + SPILED_REG_LED_LINE_o);
}

void check_rgb_lightening()
{
   if (shall_lighten_rgb1) {
      *rgb1_mem = (255 << 16) | (0 << 8) | 0;
   } else {
      *rgb1_mem = 0;
   }

   if (shall_lighten_rgb2) {
      *rgb2_mem = (0 << 16) | (0 << 8) | 255;
   } else {
      *rgb2_mem = 0;
   }
}

void check_rgb_timer()
{
   if (!shall_lighten_rgb1 && !shall_lighten_rgb2) {
      return;
   }

   if (shall_lighten_rgb1) {
      if (rgb1_timer >= RGB_LIGHTENED_TIME) {
         shall_lighten_rgb1 = false;
      } else {
         ++rgb1_timer;
      }
   }
   if (shall_lighten_rgb2) {
      if (rgb2_timer >= RGB_LIGHTENED_TIME) {
         shall_lighten_rgb2 = false;
      } else {
         ++rgb2_timer;
      }
   }
}

void lighten_rgb1()
{
   shall_lighten_rgb1 = true;
   rgb1_timer = 0;
}

void lighten_rgb2()
{
   shall_lighten_rgb2 = true;
   rgb2_timer = 0;
}

void lighten_led_line(int p1_score, int p2_score)
{
   for (int i = 0; i < p1_score; ++i) {
      *led_line_mem = *led_line_mem | (1 << (31 - i));
   }

   for (int j = 0; j < p2_score; ++j) {
      *led_line_mem = *led_line_mem | (1 << j);
   }
}

void reset_leds()
{
   *rgb1_mem = 0;
   shall_lighten_rgb1 = false;
   *rgb2_mem = 0;
   shall_lighten_rgb2 = false;
   *led_line_mem = 0;
}
