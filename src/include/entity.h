#pragma once
#include "core_types.h"
#include "raylib.h"

/* An entity is assumed to be a 2D rectangle with a texture and optional speed */
/* TODO: Make sure the memory alignment is right, and no memory is wasted */
typedef struct {
    Rectangle rect;
    Texture2D* texture;
    // Optional parameters for non-stationary entities
    Vector2 move_dir;
    float speed;
    Vector2 _prev_position;
} Entity;

void entity_set_asset_texture(Entity* entity, Texture2D* texture);
void entity_set_position(Entity* entity, Vector2 pos);
void entity_move(Entity* entity, bool check_out_of_window_bounds);
void entity_draw(Entity* entity, Color color);
void entity_pool_add(Entity* entity);
Vector2 entity_get_position(Entity* entity);
Vector2 entity_get_middle_point(Entity* entity);
bool entity_is_out_of_window_bounds(Entity* entity);
bool entity_is_colliding(Entity* entity_a, Entity* entity_b, bool check_self);
