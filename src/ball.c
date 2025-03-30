#include "include/ball.h"

void ball_move(Ball* ball, Vector2 dir) {
    ball->base.position.x += dir.x * ball->speed;
    ball->base.position.y += dir.y * ball->speed;
}
