#include "include/entity.h"

#include "include/globals.h"
#include "raylib.h"

void entity_set_asset_texture(Entity* entity, Texture2D* texture) { entity->texture = texture; }

void entity_move(Entity* entity, bool check_out_of_window_bounds) {
    entity->_prev_position = (Vector2){entity->rect.x, entity->rect.y};

    Vector2 velocity =
        (Vector2){entity->speed * entity->move_dir.x, entity->speed * entity->move_dir.y};

    entity->rect.x += velocity.x;
    entity->rect.y += velocity.y;

    if (check_out_of_window_bounds && entity_is_out_of_window_bounds(entity)) {
        entity->rect.x = entity->_prev_position.x;
        entity->rect.y = entity->_prev_position.y;
    }
}

void entity_draw(Entity* entity, Color color) {
    DrawTexture(*entity->texture, entity->rect.x, entity->rect.y, color);
}

void entity_set_position(Entity* entity, Vector2 pos) {
    entity->rect.x = pos.x;
    entity->rect.y = pos.y;
}

Vector2 entity_get_position(Entity* entity) { return (Vector2){entity->rect.x, entity->rect.y}; }

Vector2 entity_get_middle_point(Entity* entity) {
    return (Vector2){
        entity->rect.x - entity->rect.width / 2.0f,
        entity->rect.y - entity->rect.height / 2.0f,
    };
}

bool entity_is_out_of_window_bounds(Entity* entity) {
    return ((entity->rect.y + entity->rect.height > WINDOW_HEIGHT) || (entity->rect.y < 0)) ||
           ((entity->rect.x + entity->rect.width > WINDOW_WIDTH) || (entity->rect.x < 0));
}

bool entity_is_colliding(Entity* entity_a, Entity* entity_b, bool check_self) {
    if (check_self && entity_a == entity_b) {
        return false;
    }

    return CheckCollisionRecs(entity_a->rect, entity_b->rect);
}
