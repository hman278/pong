#include "include/entity.h"

#include "include/asset_texture.h"

void entity_set_texture(Entity* entity, AssetTexture* texture) { entity->asset_texture = texture; }

void entity_set_position(Entity* entity, Vector2 pos) {
    entity->rect.x = pos.x;
    entity->rect.y = pos.y;
}

/* TODO: Add screen bound checking */
void entity_move(Entity* entity, Vector2 move_dir) {
    Vector2 velocity = (Vector2){entity->speed * move_dir.x, entity->speed * move_dir.y};

    entity->rect.x += velocity.x;
    entity->rect.y += velocity.y;
}

/* Draws texture on screen centered */
void entity_draw(Entity* entity, float frame_count, Color color) {
    DrawTextureRec(
        entity->asset_texture->texture, entity->rect,
        (Vector2){entity->rect.x - entity->asset_texture->texture.width / 2.f,
                  entity->rect.y - entity->asset_texture->texture.height / 2.f / frame_count},
        color);
}
