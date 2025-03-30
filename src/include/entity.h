#pragma once
#include "core_types.h"

/* TODO: Make sure the memory alignment is right, and no memory is wasted */
typedef struct {
    Rectangle rect;
    Texture2D* texture;
    /* Define the number of frames for our sprite */
    int frame_count;
    float speed;
} Entity;

void entity_set_texture(Entity* entity, Texture2D* texture);
void entity_set_position(Entity* entity, Vector2 pos);
void entity_move(Entity* entity, Vector2 move_dir, bool check_can_move);
bool entity_can_move(Entity* entity);
