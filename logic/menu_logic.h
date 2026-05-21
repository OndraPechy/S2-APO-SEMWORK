#include <stdbool.h>
#ifndef MENU_LOGIC_H
#define MENU_LOGIC_H

/**
 * @brief Represents the state of the application.
 * Used in the main application while-loop to determine which screen
 * should be currently used.
 */
typedef enum
{
   MAIN_MENU,
   ONE_PLAYER_MENU,
   TWO_PLAYERS_MENU,
   PAUSE_MENU,
   END_MENU,
   GAME_SCREEN
} app_state_t;

/**
 * @brief Represents the chosen bot difficulty (1 player).
 */
typedef enum
{
   NONE_DIFFICULTY_CHOSEN,
   EASY_DIFFICULTY_CHOSEN,
   MEDIUM_DIFFICULTY_CHOSEN,
   HARD_DIFFICULTY_CHOSEN,
} one_player_difficulty_t;

/**
 * @brief Represents the winner of the game.
 */
typedef enum
{
   RED_PLAYER,
   BLUE_PLAYER,
} winner_t;

/**
 * @brief Routes the rendering call to the appropriate menu drawing function.
 * @param state The current state of the application.
 */
void showMenu(app_state_t state);

/**
 * @brief Determines the number of selectable options for a given menu screen.
 * @param current_state The current application state.
 * @return int The total number of clickable options.
 */
int get_menu_options_count(int current_state);

/**
 * @brief Moves the menu cursor forward.
 * @param state The current application state.
 */
void increment_cursor(app_state_t state);

/**
 * @brief Moves the menu cursor backward.
 * @param state The current application state.
 */
void decrement_cursor(app_state_t state);

/**
 * @brief Increases the target score up.
 */
void increment_score();

/**
 * @brief Decreases the target score up.
 */
void decrement_score();

/**
 * @brief Executes the action associated with the currently highlighted menu button.
 * @param appRunning Pointer to the main loop flag.
 * @param state Pointer to the current application state.
 */
void make_menu_action(bool *appRunning, app_state_t *state);

/**
 * @brief Resets the menu values.
 */
void reset_values();

/**
 * @brief Generates a formatted string representing the selected bot difficulty.
 * @param difficulty The current difficulty value.
 * @return const char* Pointer to a static string buffer containing the formatted text.
 */
const char *get_difficulty_string(int difficulty);

/**
 * @brief Generates a formatted string representing the the current playing score.
 * @param score The current playing score.
 * @return const char* Pointer to a static string buffer containing the formatted text.
 */
const char *get_score_string(int score);

/**
 * @brief Generates a formatted string representing the the winner colour.
 * @param winner The winner of the game.
 * @return const char* Pointer to a static string buffer containing the formatted text.
 */
const char *get_winner_string(int winner);

/**
 * @brief Maps the selected difficulty to its corresponding color.
 * @return int The 16-bit color code representing the difficulty.
 */
int get_difficulty_colour();

#endif /* MENU_LOGIC_H */
