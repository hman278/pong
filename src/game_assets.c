#include "include/game_assets.h"

#include <raylib.h>
#include <stdio.h>

GameAssets g_assets;

/* TODO: Hard coded values and function calls, address it, maybe */
void game_assets_load(void) {
    Texture2D racket_texture = LoadTexture("resources/racket.png");
    Texture2D ball_texture = LoadTexture("resources/ball.png");

    g_assets.racket_asset_texture = (AssetTexture){.texture = racket_texture, .v_frame_count = 2};
    g_assets.ball_asset_texture = (AssetTexture){.texture = ball_texture, .v_frame_count = 1};
}

void game_assets_unload(void) {
    UnloadTexture(g_assets.racket_asset_texture.texture);
    UnloadTexture(g_assets.ball_asset_texture.texture);
}
