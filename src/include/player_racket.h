#pragma once
#include <stdlib.h>

#include "core_types.h"
#include "entity.h"

#define PLAYER_OFFSET_X 20.0f

#define PLAYER_RACKET_A_START_POS \
    ((Vector2){PLAYER_OFFSET_X,   \
               ((GetScreenHeight() / 2.0f) - ((float)g_assets.racket_texture.height / 2.0f))})

#define PLAYER_RACKET_B_START_POS                                                  \
    ((Vector2){GetScreenWidth() - PLAYER_OFFSET_X - g_assets.racket_texture.width, \
               ((GetScreenHeight() / 2.0f) - ((float)g_assets.racket_texture.height / 2.0f))})

#define PLAYER_RACKET_WIDTH g_assets.racket_texture.width
#define PLAYER_RACKET_HEIGHT g_assets.racket_texture.height

#define PLAYER_DEFAULT_SPEED 5

typedef struct {
    Entity base;
    int score;
} PlayerRacket;
