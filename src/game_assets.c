#include "include/game_assets.h"

#include <raylib.h>
#include <stdio.h>

GameAssets g_assets;

/* TODO: Hard coded values and function calls, address it, maybe */
void game_assets_load(void) {
    g_assets.racket_texture = LoadTexture("resources/racket.png");
    g_assets.ball_texture = LoadTexture("resources/ball.png");
}

void game_assets_unload(void) {
    UnloadTexture(g_assets.racket_texture);
    UnloadTexture(g_assets.ball_texture);
}
