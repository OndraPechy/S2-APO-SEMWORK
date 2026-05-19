// toto jsou include guardy ktere jsou potreba kdyz vic souboru includuje tento
#ifndef FONT_RENDER_H
#define FONT_RENDER_H

#include "font_types.h"

// EXTERN PISU DO HLAVICKOVYCH
extern font_descriptor_t font_winFreeSystem14x16; // musi se skutecne jmenovat takhle protoze timhle
                             // vlastne programu rikam
// ze budu jinde hledat promennou s timto nazvem, a takto se jmenuje v tom
// souboru font_prop14x16.c

// tim ze tomu tady dam extern, tak rikam, ze k tomu budu moct pristoupit z jinych souboru
extern unsigned short *frame_buffer;

void draw_word(char *word, int pos_x, int pos_y, unsigned short int color, int scale);
int draw_char(char letter, int pos_x, int pos_y, unsigned short int color, int scale);
void draw_pixel(int x, int y, unsigned short int color);

#endif /* FONT_DRAWER_H */
