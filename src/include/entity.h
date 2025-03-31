#pragma once
#include "asset_texture.h"
#include "core_types.h"

/* TODO: Make sure the memory alignment is right, and no memory is wasted */
typedef struct {
    Rectangle rect;
    AssetTexture* asset_texture;
    float speed;
} Entity;

void entity_set_asset_texture(Entity* entity, AssetTexture* asset_texture);
void entity_set_position(Entity* entity, Vector2 pos);
void entity_move(Entity* entity, Vector2 move_dir);
void entity_draw(Entity* entity, Color color);
