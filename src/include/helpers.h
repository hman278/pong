#pragma once
#include "include/core_types.h"
#include "include/entity.h"
#include "include/player_racket.h"

static inline Rectangle rect_create(float x, float y, float w, float h) {
    return (Rectangle){x, y, w, h};
}

static inline Entity entity_create(float x, float y, float w, float h, Texture2D* texture,
                                   int frame_count, float speed) {
    return (Entity){.rect = rect_create(x, y, w, h),
                    .texture = texture,
                    .frame_count = frame_count,
                    .speed = speed};
}

static inline PlayerRacket player_create(float x, float y, float width, float height,
                                         Texture2D* texture, int frame_count, float speed) {
    return (PlayerRacket){.base = entity_create(x, y, width, height, texture, frame_count, speed),
                          .score = 0};
}
