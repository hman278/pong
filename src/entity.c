#include "include/entity.h"

void entity_set_texture(Entity* entity, Texture2D* texture) { entity->texture = texture; }

void entity_set_position(Entity* entity, Vector2 pos) {
    entity->rect.x = pos.x;
    entity->rect.y = pos.y;
}

void entity_move(Entity* entity, Vector2 move_dir, bool check_can_move) {
    Vector2 velocity = (Vector2){entity->speed * move_dir.x, entity->speed * move_dir.y};

    if (check_can_move && !entity_can_move(entity)) {
        return;
    }

    entity->rect.x += velocity.x;
    entity->rect.y += velocity.y;
}

/* It is prohibited to move outside of the window bounds */
bool entity_can_move(Entity* entity) {
    return (entity->rect.y >= entity->texture->height / 2.0f / entity->frame_count) &&
           ((GetScreenHeight() - entity->texture->height / 2.0f / entity->frame_count));
}
