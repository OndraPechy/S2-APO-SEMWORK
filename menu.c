#include <stdint.h>

#include "menu.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"






// im using an enum as states because there will be a while loop that will look
// at a state of a menu each time
enum menuStates
{
   MAIN_MENU,
   ONE_PLAYER_MENU,
   TWO_PLAYERS_MENU,
   PAUSE_MENU,
   END_MENU,
};

enum mainMenuCursor
{
   ONE_PLAYER_CHOICE,
   TWO_PLAYERS_CHOICE,
   EXIT_CHOICE,
};

// NASTAVOVANI POCTU BODU SE BUDE DELAT PRES KNOB

enum onePlayerMenuCursor
{
   EASY_DIFFICULTY,
   MEDIUM_DIFFICULTY,
   HARD_DIFFICULTY,
};

enum pauseMenuCursor
{
   RESUME_CHOICE,
   LEAVE_GAME_SCREEN_CHOICE,
};

enum endMenuCursor
{
   RETURN_TO_MENU_CHOICE,
   EXIT_CHOICE,
};

// budu mit staticky ukazatel pozice toho knobu a
static uint8_t green_knob_previous_position;

void showMenu()
{
}

char get_knob_value(int mask, int shift, uint32_t *knob_mem_base)
{
   int value = *knob_mem_base;
   value = value & mask;
   return value >> shift;
}
