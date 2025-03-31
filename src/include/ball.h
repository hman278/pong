#pragma once
#include "core_types.h"
#include "entity.h"

#define BALL_START_POS                                                                     \
    ((Vector2){GetScreenWidth() / 2.0f - g_assets.ball_asset_texture.texture.width / 2.0f, \
               GetScreenHeight() / 2.0f - g_assets.ball_asset_texture.texture.height / 2.0f})

typedef struct {
    Entity base;
} Ball;
