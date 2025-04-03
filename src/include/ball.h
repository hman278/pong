#pragma once
#include "core_types.h"
#include "entity.h"

#define BALL_START_POS                                                       \
    ((Vector2){GetScreenWidth() / 2.0f - g_assets.ball_texture.width / 2.0f, \
               GetScreenHeight() / 2.0f - g_assets.ball_texture.height / 2.0f})

#define BALL_SIZE g_assets.ball_texture.width
#define BALL_DEFAULT_SPEED 4.0f

typedef struct {
    Entity base;
} Ball;
