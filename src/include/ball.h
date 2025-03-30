#pragma once
#include "core_types.h"

#define BALL_START_POS ((Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f})

typedef struct {
    Texture2D* texture;
    Rectangle* rect;
    float speed;
} Ball;
