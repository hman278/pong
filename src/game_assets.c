#include "include/game_assets.h"

#include <raylib.h>

GameAssets g_assets;

/* TODO: Fix the hard code */
void game_assets_load(void) {
    g_assets.racket_asset_texture =
        (AssetTexture){.texture = LoadTexture("resources/racket.png"), .v_frame_count = 2};

    g_assets.ball_asset_texture =
        (AssetTexture){.texture = LoadTexture("resources/ball.png"), .v_frame_count = 1};
}

void game_assets_unload(void) {
    UnloadTexture(g_assets.racket_asset_texture.texture);
    UnloadTexture(g_assets.ball_asset_texture.texture);
}
