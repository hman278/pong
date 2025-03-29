#pragma once
#include "core_types.h"
#include "entity.h"

typedef struct {
    Entity base;
    float speed;
    Rectangle rect;
} Ball;
