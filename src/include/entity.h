#pragma once
#include "core_types.h"
#include "raylib.h"

/* An entity is assumed to be a 2D rectangle with a texture and optional speed */
/* TODO: Make sure the memory alignment is right, and no memory is wasted */
typedef struct {
    Rectangle rect;
    Texture2D* texture;
    Vector2 move_dir;
    float speed;
} Entity;

void entity_set_asset_texture(Entity* entity, Texture2D* texture);
void entity_set_position(Entity* entity, Vector2 pos);
Vector2 entity_get_middle_point(Entity* entity);
void entity_move(Entity* entity);
void entity_draw(Entity* entity, Color color);
