#pragma once
#include "include/core_types.h"
#include "include/entity.h"
#include "include/player_racket.h"

static inline Rectangle rect_create(float x, float y, float w, float h) {
    return (Rectangle){x, y, w, h};
}

static inline Entity entity_create(float x, float y, float w, float h, AssetTexture* texture,
                                   int frame_count, float speed) {
    Entity entity = (Entity){.rect = rect_create(x, y, w, h),
                             .texture = texture,
                             .frame_count = frame_count,
                             .speed = speed};

    entity_set_texture(&entity, texture);
    entity_set_position(&entity, (Vector2){x, y});

    return entity;
}

static inline PlayerRacket player_racket_create(float x, float y, float width, float height,
                                                AssetTexture* texture, int frame_count,
                                                float speed) {
    Entity entity = entity_create(x, y, width, height, texture, frame_count, speed);

    return (PlayerRacket){.base = entity, .score = 0};
}
