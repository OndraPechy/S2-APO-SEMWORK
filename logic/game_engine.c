#include "game_engine.h"
#include "ball.h"
#include "paddle.h"
#include "render.h"
#include "leds_setup.h"

static ball_t ball;
static paddle_t left_p;
static paddle_t right_p;
static int score_left;
static int score_right;
static int target;
static int mode;
static int ai_difficulty;
static game_state_t state;
static winner_t winner;


/* internal helper, shared by both start_game_* variants */
static void start_game_common(int target_score);

void start_game_1p(int difficulty, int target_score) {
    mode = 1;
    ai_difficulty = difficulty;
    start_game_common(target_score);
}

void start_game_2p(int target_score) {
    mode = 2;
    ai_difficulty = 0;
    start_game_common(target_score);
}

static void start_game_common(int target_score) {
    target = target_score;
    score_left = 0;
    score_right = 0;
    reset_ball(&ball);

    left_p.y = 160;
    left_p.height = 100;
    left_p.width = 20;
    left_p.left = true;
    
    right_p.y = 160;
    right_p.height = 100;
    right_p.width = 20;
    right_p.left = false;

    state = PLAYING;
    winner = RED_PLAYER; //default, overwritten on finish
}

void game_tick(int left_delta, int right_delta){
    if (state != PLAYING){
        return;
    }
    
    // update left paddle: AI in 1P, player in 2P
    if (mode == 1){
        int ai_speed = (ai_difficulty == 1) ? EASY_BOT_SPEED
                     : (ai_difficulty == 2) ? MEDIUM_BOT_SPEED
                     : HARD_BOT_SPEED;
        update_bot_paddle(&left_p, &ball, ai_speed);
    }
    if (mode == 2){
        update_paddle(&left_p, left_delta);
    }
    // right paddle is always player
    update_paddle(&right_p, right_delta);
    state_t result = update_ball(&ball, &left_p, &right_p);

    // handle goal, increment score and flash the corresponding RGB LED
    if (result == SCORES_LEFT){
        score_left++;
        lighten_rgb1(); 
    } else if(result == SCORES_RIGHT){
        score_right++;
        lighten_rgb2();
    }

    // endgame detection
    if(score_left >= target){
        state = FINISHED;
        winner = RED_PLAYER;
    }
    if(score_right >= target){
        state = FINISHED;
        winner = BLUE_PLAYER;
    }
    lighten_led_line(score_left, score_right);
    render_game(&ball, &left_p, &right_p);
}

void pause_game(void){
    state = PAUSED;
}

void resume_game(void){
    state = PLAYING;
}

void stop_game(void){
    state = NOT_PLAYING;
}

bool is_game_running(void){
    return (state == PLAYING);
}

winner_t get_winner(void){
    return winner;
}

int get_score_left(void){
    return score_left;
}

int get_score_right(void){
    return score_right;
}