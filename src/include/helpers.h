#pragma once
#include "core_types.h"
#include "entity.h"

static inline Rectangle rect_create(float x, float y, float w, float h) {
    return (Rectangle){x, y, w, h};
}

static inline Vector2 vec2_create(float x, float y) { return (Vector2){x, y}; }

static inline Entity entity_create(Rectangle rect, Texture2D* texture) {
    Entity entity = {0};

    entity.rect = rect;
    entity.texture = texture;

    entity_set_asset_texture(&entity, texture);
    entity_set_position(&entity, &(Vector2){rect.x, rect.y});

    return entity;
}

static inline bool entity_has_tag(Entity* entity, EntityTag entity_tag) {
    return entity->tag == entity_tag;
}

static inline Vector2 rect_get_centered_position(Rectangle* rect) {
    return (Vector2){rect->x + rect->width / 2.0f, rect->y + rect->height / 2.0f};
}
