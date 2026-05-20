// <stddef.h> obsahuje definice zakladnich typu a maker
#include "font_render.h"
#include "font_types.h"
#include <stddef.h>

// tady nepisu extern protoze to rovnou definuji
unsigned short *frame_buffer = NULL;

extern font_descriptor_t font_winFreeSystem14x16;

void draw_word(const char *word, int pos_x, int pos_y, unsigned short int color,
               int scale)
{
   size_t index = 0;
   int current_x = pos_x;
   while (word[index] != '\0') {
      current_x += draw_char(word[index], current_x, pos_y, color, scale);
      ++index;
   }
}

int draw_char(char letter, int pos_x, int pos_y, unsigned short int color,
              int scale)
{
   // ziskam index pismena v poli fontu
   int letter_index = letter - font_winFreeSystem14x16.firstchar;
   if (letter < font_winFreeSystem14x16.firstchar ||
       letter >=
           font_winFreeSystem14x16.firstchar + font_winFreeSystem14x16.size) {
      return 0;
   }
   int font_height = font_winFreeSystem14x16.height;
   // v te strukture totiz v poli width u tohoto proporcniho textu je
   // ta spravna sirka na indexu jako je index toho pismena
   int font_width = font_winFreeSystem14x16.maxwidth; // Zachranna hodnota
   if (font_winFreeSystem14x16.width != NULL) {
      font_width = font_winFreeSystem14x16.width[letter_index];
   }
   // taky potrebuju ziskat offset kde v te mape (tom obrim poli bits) zacinaji
   // data pro dane pismeno
   uint32_t offset =
       letter_index * font_height; // Zachranna hodnota pro fixni fonty
   if (font_winFreeSystem14x16.offset != NULL) {
      offset = font_winFreeSystem14x16.offset[letter_index];
   }

   for (int height = 0; height < font_height; ++height) {
      // nactu 16 bitove cislo ktere reprezentuje jeden radek bitu toho fontu
      uint16_t row = font_winFreeSystem14x16.bits[offset + height];

      for (int width = 0; width < font_width; ++width) {
         // printuju jenom tehdy, pokud na danem miste v tom poli neni 0 (je
         // jednicka)
         if ((row & (1 << (15 - width))) != 0) {
            for (int dy = 0; dy < scale; ++dy) {
               for (int dx = 0; dx < scale; ++dx) {
                  // Základní souřadnice znásobíme měřítkem a přičteme posun
                  // uvnitř čtverce
                  draw_pixel(pos_x + (width * scale) + dx,
                             pos_y + (height * scale) + dy, color);
               }
            }
         }
         // vratim font width aby se mohlo vratit dal
      }
   }
   return font_width * scale;
}

void draw_pixel(int x, int y, unsigned short int color)
{
   // bude kresli jen tehdy, pokud se trefi do rozmeru displeje
   if (x >= 0 && x < 480 && y >= 0 && y < 320) {
      frame_buffer[x + 480 * y] = color;
   }
}
