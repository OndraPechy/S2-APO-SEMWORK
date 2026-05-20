#ifndef LEDS_SETUP_H
#define LEDS_SETUP_H

void setup_leds(unsigned char *mem_base);
void check_rgb_lightening();
void check_rgb_timer();
void lighten_rgb1();
void lighten_rgb2();
void lighten_led_line(int p1_score, int p2_score);
void reset_leds();

#endif /*LEDS_SETUP_H*/
