#pragma once
#include "core_types.h"
#include "entity.h"

/* TODO: Make sure the memory alignment is right, and no memory is wasted */
typedef struct {
    Entity base;
    float speed;
    Rectangle rect;
    /* Define the number of frames for our racket sprite */
    int frame_count;
    int score;
} PlayerRacket;

bool player_can_move(PlayerRacket* player_racket);
void player_move(PlayerRacket* player_racket, Vector2 move_dir);
