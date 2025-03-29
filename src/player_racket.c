#include "player_racket.h"

bool player_can_move(PlayerRacket* player_racket) {
    return (player_racket->base.position.y >=
            player_racket_texture.height / 2.0f / player_racket->frame_count) &&
           ((GetScreenHeight() - player_racket_texture.height / 2.0f / player_racket->frame_count));
}

void player_move(PlayerRacket* player_racket, Vector2 move_dir) {
    player_racket->base.position.y += player_racket->speed * Vector2Length(move_dir);
}
