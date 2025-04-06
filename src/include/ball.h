#pragma once
#include "core_types.h"
#include "entity.h"
#include "helpers.h"

#define BALL_START_POS                                                       \
    ((Vector2){GetScreenWidth() / 2.0f - g_assets.ball_texture.width / 2.0f, \
               GetScreenHeight() / 2.0f - g_assets.ball_texture.height / 2.0f})

#define BALL_SIZE g_assets.ball_texture.width
#define BALL_DEFAULT_SPEED 4.0f

typedef struct {
    Entity base;
} Ball;

Vector2 ball_calculate_bounce_direction(Entity* entity_ball, Entity* entity_collider) {
    Vector2 ball_centered_position = rect_get_centered_position(&entity_ball->rect);
    Vector2 entity_collider_centered_position = rect_get_centered_position(&entity_collider->rect);

    // It is required to have player-specific logic handling, since player
    // rackets do not follow the same bouce logic, as the rest of the entities
    if (entity_has_tag(entity_collider, PLAYER)) {
        float ball_player_offset =
            (ball_centered_position.y - entity_collider_centered_position.y) /
            (entity_collider->rect.height / 2.0f);
    }

    Vector2 ball_collision_direction =
        Vector2Normalize(Vector2Subtract(ball_centered_position, collision_point));

    return
}
