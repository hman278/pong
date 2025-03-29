#pragma once
#include "core_types.h"

typedef struct {
    Texture2D racket_texture;
    Texture2D ball_texture;
} GameAssets;

extern GameAssets g_assets;
void load_game_assets(void);
void unload_game_asset(void);
