#include "include/game_assets.h"

#include <raylib.h>

GameAssets g_assets;

/* TODO: Fix the hard code */
void load_game_assets(void) {
    g_assets.racket_texture.texture = LoadTexture("resources/racket.png");
    g_assets.racket_texture.v_frame_count = 2;

    g_assets.ball_texture.texture = LoadTexture("resources/ball.png");
    g_assets.ball_texture.v_frame_count = 1;
}

void unload_game_asset(void) {
    UnloadTexture(g_assets.racket_texture.texture);
    UnloadTexture(g_assets.ball_texture.texture);
}
