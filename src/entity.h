#pragma once
#include "core_types.h"

typedef struct {
    Texture2D* texture;
    /* Represents the centered position of the entity */
    Vector2 position;
} Entity;
