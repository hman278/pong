#pragma once
#include "asset_texture.h"
#include "core_types.h"

typedef struct {
    AssetTexture racket_asset_texture;
    AssetTexture ball_asset_texture;
} GameAssets;

extern GameAssets g_assets;
void game_assets_load(void);
void game_assets_unload(void);
