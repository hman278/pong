#pragma once
#include "core_types.h"
#include "raylib.h"

typedef struct {
    Texture2D racket_texture;
    Texture2D ball_texture;
} GameAssets;

extern GameAssets g_assets;
void game_assets_load(void);
void game_assets_unload(void);
