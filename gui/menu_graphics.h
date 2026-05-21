#ifndef MENU_GRAPHICS_H
#define MENU_GRAPHICS_H

/**
 * @brief Identifiers for the clickable buttons in the Main Menu.
 */
typedef enum
{
   ONE_PLAYER_CHOICE_BUTTON,
   TWO_PLAYERS_CHOICE_BUTTON,
   MM_EXIT_CHOICE_BUTTON
} main_menu_cursor_t;

/**
 * @brief Identifiers for the clickable buttons in the 1 Player Menu.
 */
typedef enum
{
   EASY_DIFFICULTY_BUTTON,
   MEDIUM_DIFFICULTY_BUTTON,
   HARD_DIFFICULTY_BUTTON,
   GO_BACK_1_PLAYER_BUTTON,
   START_GAME_1_PLAYER_BUTTON
} one_player_menu_cursor_t;

/**
 * @brief Identifiers for the clickable buttons in the 2 Players Menu.
 */
typedef enum
{
   GO_BACK_2_PLAYERS_BUTTON,
   START_GAME_2_PLAYERS_BUTTON
} two_players_menu_cursor_t;

/**
 * @brief Identifiers for the clickable buttons in the Pause Menu.
 */
typedef enum
{
   RESUME_CHOICE_BUTTON,
   LEAVE_GAME_SCREEN_CHOICE_BUTTON
} pause_menu_cursor_t;

/**
 * @brief Identifiers for the clickable buttons in the End Menu.
 */
typedef enum
{
   RETURN_TO_MENU_CHOICE_BUTTON,
   EXIT_CHOICE_BUTTON
} end_menu_cursor_t;

/**
 * @brief Renders the Main Menu screen to the frame buffer.
 * @param cursor The currently selected option to be highlighted.
 */
void draw_main_menu(main_menu_cursor_t cursor);

/**
 * @brief Renders the 1 Player Menu.
 * * @param cursor The currently selected option to be highlighted.
 * @param score_string Formatted string displaying the current target score.
 * @param difficulty_string Formatted string displaying the selected bot difficulty.
 * @param difficulty_colour The 16-bit color corresponding to the chosen difficulty.
 * @param score The raw target score integer.
 */
void draw_one_player_menu(one_player_menu_cursor_t cursor,
                          const char *score_string,
                          const char *difficulty_string, int difficulty_colour,
                          int score);

/**
 * @brief Renders the 2 Players Menu.
 * @param cursor The currently selected option to be highlighted.
 * @param score_string Formatted string displaying the current target score.
 * @param score The raw target score integer.
 */
void draw_two_players_menu(two_players_menu_cursor_t cursor,
                           const char *score_string, int score);

/**
 * @brief Renders the Pause Menu.
 * @param cursor The currently selected option to be highlighted.
 */
void draw_pause_menu(pause_menu_cursor_t cursor);

/**
 * @brief Renders the End Menu.
 * @param cursor The currently selected option to be highlighted.
 * @param winner_string Formatted string announcing the winner.
 * @param winner Integer identifier of the winning player.
 */
void draw_end_menu(end_menu_cursor_t cursor, const char *winner_string,
                   int winner);

/**
 * @brief Calculates a dynamic color for the score text.
 * @param multiplier The current score value.
 * @return int The calculated 16-bit color code.
 */
int get_score_color(int multiplier);

#endif /* MENU_GRAPHICS_H */
