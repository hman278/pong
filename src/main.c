/*******************************************************************************************
 *
 *   Copyright (c) 2025 @hman278
 *
 ********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/ball.h"
#include "include/core_types.h"
#include "include/entity.h"
#include "include/game_assets.h"
#include "include/globals.h"
#include "include/helpers.h"
#include "include/player_racket.h"
#include "raylib.h"
#include "raymath.h"

typedef enum { MENU, PAUSED, WAITING, ONGOING } GameState;

#define FPS_POS_X 10
#define FPS_POS_Y 420
#define WALL_THICKNESS 20.0f
#define ENTITY_COUNT 5

/* Globals */
GameState g_game_state;

PlayerRacket g_player_racket_a, g_player_racket_b;
Ball g_ball;
Entity g_wall_top, g_wall_bottom;

PlayerRacket* g_serving_player;
PlayerRacket* g_last_ball_hit_player;

// Decided not to overengineer and keep things simple here,
// since the entity count is small and known
Entity* g_entities[ENTITY_COUNT];

/* TODO: Make the ball go to the serving player */
void reset_entity_positions() {
    entity_set_position(&(g_player_racket_a.base), &PLAYER_RACKET_A_START_POS);
    entity_set_position(&(g_player_racket_b.base), &PLAYER_RACKET_B_START_POS);
    entity_set_position(&(g_ball.base), &BALL_START_POS);
}

/* Set initial values */
void init() {
    game_assets_load();

    Rectangle rect_player_racket_a =
        rect_create(PLAYER_RACKET_A_START_POS.x, PLAYER_RACKET_A_START_POS.y, PLAYER_RACKET_WIDTH,
                    PLAYER_RACKET_HEIGHT);
    Rectangle rect_player_racket_b =
        rect_create(PLAYER_RACKET_B_START_POS.x, PLAYER_RACKET_B_START_POS.y, PLAYER_RACKET_WIDTH,
                    PLAYER_RACKET_HEIGHT);
    Rectangle rect_ball = rect_create(BALL_START_POS.x, BALL_START_POS.y, BALL_SIZE, BALL_SIZE);
    Rectangle rect_wall_top = rect_create(0.0f, -WALL_THICKNESS, WINDOW_WIDTH, WALL_THICKNESS);
    Rectangle rect_wall_bottom = rect_create(0.0f, WINDOW_HEIGHT, WINDOW_WIDTH, WALL_THICKNESS);

    g_player_racket_a = (PlayerRacket){
        .base = entity_create(rect_player_racket_a, &g_assets.racket_texture), .score = 0};
    g_player_racket_b = (PlayerRacket){
        .base = entity_create(rect_player_racket_b, &g_assets.racket_texture), .score = 0};

    g_ball = (Ball){.base = entity_create(rect_ball, &g_assets.ball_texture)};
    // Create invisible walls for the top and bottom of the screen
    g_wall_top = entity_create(rect_wall_top, NULL);
    g_wall_bottom = entity_create(rect_wall_bottom, NULL);

    Entity* entities[ENTITY_COUNT] = {&g_player_racket_a.base, &g_player_racket_b.base,
                                      &g_ball.base, &g_wall_top, &g_wall_bottom};
    memcpy(g_entities, entities, sizeof(g_entities));

    g_player_racket_a.base.speed = PLAYER_RACKET_DEFAULT_SPEED;
    g_player_racket_b.base.speed = PLAYER_RACKET_DEFAULT_SPEED;
    g_ball.base.speed = BALL_DEFAULT_SPEED;

    g_player_racket_a.base.tag = g_player_racket_b.base.tag = PLAYER;

    // Player A is the default serving player
    // TODO: If rematch behavior is added, remember the player who lost the previous game
    g_serving_player = &g_player_racket_a;
    g_last_ball_hit_player = g_serving_player;

    float dx = g_ball.base.rect.x - g_serving_player->base.rect.x;
    g_ball.base.move_dir = Vector2Normalize((Vector2){dx, 0.0f});
}

void shutdown() { game_assets_unload(); }

void update() {
    g_player_racket_a.base.move_dir.y = (int)IsKeyDown(KEY_S) - IsKeyDown(KEY_W);
    g_player_racket_b.base.move_dir.y = (int)IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP);

    entity_move(&g_player_racket_a.base, true);
    entity_move(&g_player_racket_b.base, true);
    entity_move(&g_ball.base, false);

    for (int i = 0; i < ENTITY_COUNT; ++i) {
        Entity* collider_entity = g_entities[i];
        Vector2 collision_point;
        if (entity_is_colliding(&g_ball.base, collider_entity, &collision_point, true)) {
            g_ball.base.move_dir =
                ball_calculate_bounce_direction(&g_ball.base, collider_entity, &collision_point);
            break;
        }
    }

    /* sprintf(debugText, "%f", (Ball.position.y - PlayerA.position.y) / -90.f); */
    /* sprintf(playerAScoreStr, "%i", PlayerAScore); */
    /* sprintf(playerBScoreStr, "%i", PlayerBScore); */
}

int main(void) {
    // Initialization
    //-------------------------------------------------------------------------------------

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Raylib Pong");

    SetTargetFPS(120);  // Set our game to run at 120 frames-per-second
    //--------------------------------------------------------------------------------------

    init();

    // Main game loop
    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        // Update
        update();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        entity_draw((Entity*)&g_player_racket_a.base, BLUE);
        entity_draw((Entity*)&g_player_racket_b.base, RED);
        entity_draw((Entity*)&g_ball.base, GREEN);

        DrawFPS(FPS_POS_X, FPS_POS_Y);

        /* DrawText(playerAScoreStr, 10, 10, 30, BLUE); */
        /* DrawText(playerBScoreStr, 740, 10, 30, BLUE); */

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();  // Close window and OpenGL context
    shutdown();
    //--------------------------------------------------------------------------------------

    return 0;
}
