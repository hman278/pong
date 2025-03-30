#pragma once
#include <stdlib.h>

#include "core_types.h"
#include "entity.h"

#define PLAYER_OFFSET_X 20.0f
#define PLAYER_A_START_POS ((Vector2){PLAYER_OFFSET_X, GetScreenHeight() / 2.0f})
#define PLAYER_B_START_POS ((Vector2){GetScreenWidth() - PLAYER_OFFSET_X, GetScreenHeight() / 2.0f})
#define PLAYER_DEFAULT_SPEED 1

typedef struct {
    Entity base;
    int score;
} PlayerRacket;
