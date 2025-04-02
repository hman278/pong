#pragma once
#include "core_types.h"
#include "entity.h"

static inline Rectangle rect_create(float x, float y, float w, float h) {
    return (Rectangle){x, y, w, h};
}

static inline Entity entity_create(Rectangle rect, Texture2D* texture) {
    Entity entity = (Entity){.rect = rect, .texture = texture};

    entity_set_asset_texture(&entity, texture);
    entity_set_position(&entity, (Vector2){rect.x, rect.y});

    return entity;
}
