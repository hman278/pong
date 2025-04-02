#include "include/entity.h"

void entity_set_asset_texture(Entity* entity, Texture2D* texture) { entity->texture = texture; }

void entity_set_position(Entity* entity, Vector2 pos) {
    entity->rect.x = pos.x;
    entity->rect.y = pos.y;
}

Vector2 entity_get_middle_point(Entity* entity) {
    return (Vector2){
        entity->rect.x - entity->rect.width / 2.0f,
        entity->rect.y - entity->rect.height / 2.0f,
    };
}

/* TODO: Add screen bound checking */
void entity_move(Entity* entity) {
    Vector2 velocity =
        (Vector2){entity->speed * entity->move_dir.x, entity->speed * entity->move_dir.y};

    entity->rect.x += velocity.x;
    entity->rect.y += velocity.y;
}

/* TODO: Check if the drawing coordinates are correct */
void entity_draw(Entity* entity, Color color) {
    DrawTexture(*entity->texture, entity->rect.x, entity->rect.y, color);
}
