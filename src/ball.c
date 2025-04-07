#include "ball.h"

#include "core_types.h"
#include "helpers.h"
#include "player_racket.h"

Vector2 ball_calculate_bounce_direction(Entity* entity_ball, Entity* entity_collider,
                                        Vector2* collision_point) {
    Vector2 ball_centered_position = rect_get_centered_position(&entity_ball->rect);
    Vector2 entity_collider_centered_position = rect_get_centered_position(&entity_collider->rect);
    Vector2 ball_collision_direction =
        Vector2Normalize(Vector2Subtract(ball_centered_position, *collision_point));

    Vector2 ball_bounce_direction = {0};

    // It is required to have player-specific logic handling, since player
    // rackets do not follow the same bouce logic, as the rest of the entities (walls)
    if (entity_has_tag(entity_collider, PLAYER)) {
        float vertical_offset = (ball_centered_position.y - entity_collider_centered_position.y) /
                                (entity_collider->rect.height / 2.0f);

        float vertical_friction =
            (entity_get_velocity(entity_collider).y * PLAYER_RACKET_DEFAULT_FRICTION);

        ball_bounce_direction.x = ball_collision_direction.x;
        ball_bounce_direction.y += vertical_offset + vertical_friction;
    } else {
        ball_bounce_direction.x = entity_ball->move_dir.x;
        ball_bounce_direction.y = -entity_ball->move_dir.y;
    }

    return Vector2Normalize(ball_bounce_direction);
}
