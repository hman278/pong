#pragma once
#include "core_types.h"
#include "include/asset_texture.h"

typedef struct {
    AssetTexture racket_asset_texture;
    AssetTexture ball_asset_texture;
} GameAssets;

extern GameAssets g_assets;
void load_game_assets(void);
void unload_game_assets(void);
