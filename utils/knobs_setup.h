#include <stdint.h>
#include <stdbool.h>
#ifndef KNOBS_SETUP_H
#define KNOBS_SETUP_H

void setup_knobs(unsigned char *mem_base);
void check_knobs();
void update_green_knob();
void update_red_knob();
void update_blue_knob();
void update_green_knob_pressed();
bool green_knob_moved_up();
bool green_knob_moved_down();
bool blue_knob_moved_up();
bool blue_knob_moved_down();
bool red_knob_moved_up();
bool red_knob_moved_down();
bool is_green_knob_clicked();
char get_knobs_value(int mask, int shift, uint32_t *knob_mem_base);

#endif /*KNOBS_SETUP_H*/
