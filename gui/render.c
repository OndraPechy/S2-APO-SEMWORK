#include "render.h"
#include "shape_render.h"

/**
 * Colors are defined as RGB565 literals:
 *   WHITE 0xFFFF, RED 0xF800, BLUE 0x001F
 */
void render_game(ball_t* ball, paddle_t* left_p, paddle_t* right_p){
    draw_rect(240, 160, 2, 320, WHITE);
    draw_rect(240, 1, 480, 2, WHITE);
    draw_rect(240, 318, 480, 2, WHITE);
    
    draw_paddle(left_p, RED);
    draw_paddle(right_p, BLUE);
    
    draw_rect(ball->x, ball->y, ball->size, ball->size, WHITE);
}