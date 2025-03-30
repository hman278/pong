#include "include/game_assets.h"

#include <raylib.h>

GameAssets g_assets;

void load_game_assets(void) {
    g_assets.racket_texture = LoadTexture("resources/racket.png");
    g_assets.ball_texture = LoadTexture("resources/ball.png");
}

void unload_game_asset(void) {
    UnloadTexture(g_assets.racket_texture);
    UnloadTexture(g_assets.ball_texture);
}
