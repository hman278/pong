#pragma once
#include <stdlib.h>

#include "core_types.h"
#include "entity.h"

#define PLAYER_OFFSET_X 20.0f

#define PLAYER_RACKET_A_START_POS \
    ((Vector2){PLAYER_OFFSET_X,   \
               (float)GetScreenHeight() / 2.0f / g_assets.racket_asset_texture.v_frame_count})

#define PLAYER_RACKET_B_START_POS                  \
    ((Vector2){GetScreenWidth() - PLAYER_OFFSET_X, \
               (float)GetScreenHeight() / g_assets.racket_asset_texture.v_frame_count})

#define PLAYER_RACKET_WIDTH g_assets.racket_asset_texture.width
#define PLAYER_RACKET_HEIGHT \
    g_assets.racket_asset_texture.height / g_assets.racket_texture.v_frame_count
#define PLAYER_DEFAULT_SPEED 1

typedef struct {
    Entity base;
    int score;
} PlayerRacket;
