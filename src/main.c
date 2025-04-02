/*******************************************************************************************
 *
 *   Copyright (c) 2025 @hman278
 *
 ********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "include/ball.h"
#include "include/core_types.h"
#include "include/entity.h"
#include "include/game_assets.h"
#include "include/helpers.h"
#include "include/player_racket.h"
#include "raylib.h"

typedef enum { MENU, PAUSED, WAITING, ONGOING } GameState;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define FPS_POS_X 10
#define FPS_POS_Y 420

/* Globals */
GameState g_game_state;

PlayerRacket g_player_racket_a, g_player_racket_b;
Ball g_ball;

/* TODO: Make the ball go to the serving player */
void reset_entity_positions() {
    entity_set_position(&(g_player_racket_a.base), PLAYER_RACKET_A_START_POS);
    entity_set_position(&(g_player_racket_b.base), PLAYER_RACKET_B_START_POS);
    entity_set_position(&(g_ball.base), BALL_START_POS);
}

/* Set initial values */
void init() {
    game_assets_load();

    Rectangle player_racket_a_rect =
        rect_create(PLAYER_RACKET_A_START_POS.x, PLAYER_RACKET_A_START_POS.y, PLAYER_RACKET_WIDTH,
                    PLAYER_RACKET_HEIGHT);
    Rectangle player_racket_b_rect =
        rect_create(PLAYER_RACKET_B_START_POS.x, PLAYER_RACKET_B_START_POS.y, PLAYER_RACKET_WIDTH,
                    PLAYER_RACKET_HEIGHT);

    Rectangle ball_rect = (Rectangle){BALL_START_POS.x, BALL_START_POS.y, BALL_SIZE, BALL_SIZE};

    g_player_racket_a = (PlayerRacket){
        .base = entity_create(player_racket_a_rect, &g_assets.racket_texture), .score = 0};
    g_player_racket_b = (PlayerRacket){
        .base = entity_create(player_racket_b_rect, &g_assets.racket_texture), .score = 0};
    g_ball = (Ball){.base = entity_create(ball_rect, &g_assets.ball_texture)};

    reset_entity_positions();
}

void shutdown() { game_assets_unload(); }
void update() {
    Vector2 player_a_move_dir = (Vector2){(int)IsKeyDown(KEY_W), (int)IsKeyDown(KEY_S)};
    Vector2 player_b_move_dir = (Vector2){(int)IsKeyDown(KEY_UP), (int)IsKeyDown(KEY_DOWN)};

    entity_move(&g_player_racket_a.base, player_a_move_dir);
    entity_move(&g_player_racket_b.base, player_b_move_dir);

    if (IsKeyPressed(KEY_SPACE)) {
        g_game_state = ONGOING;
    }

    /* ---- DEBUG MOUSE COORDINATES ---- */
    Vector2 mouse = GetMousePosition();

    DrawText(TextFormat("Mouse: [%.0f, %.0f]", mouse.x, mouse.y), 10, 10, 20, BLUE);
    /* --------------------------------- */

    /* Don't move the ball until someone serves it */
    /* if (g_game_state == ONGOING) { */
    /*     /1* TODO: Hardcoded value, change to match current player *1/ */
    /*     ball_move((Vector2){0, 1}); */

    /*     // TODO: calculate y direction */
    /*     if (CheckCollisionRecs( */
    /*             (Rectangle){Ball.position.x, Ball.position.y, ballRec.width, ballRec.height},
     */
    /*             (Rectangle){PlayerA.position.x + (racketRec.width / 2.f), */
    /*                         PlayerA.position.y - (racketRec.height / 2.f), racketRec.width,
     */
    /*                         racketRec.height})) { */
    /*         ballDir.x = -1; */
    /*         // lower -90 to make the ball more bouncy */
    /*         ballDir.y = (Ball.position.y - PlayerA.position.y) / -90.f; */
    /*         racketRec.y = 1 * racketTexture.height / NUM_FRAMES; */
    /*     } else if (CheckCollisionRecs( */
    /*                    (Rectangle){Ball.position.x, Ball.position.y, ballRec.width,
     * ballRec.height}, */
    /*                    (Rectangle){PlayerB.position.x - (racketRec.width / 2.f), */
    /*                                PlayerB.position.y - (racketRec.height / 2.f),
     * racketRec.width, */
    /*                                racketRec.height})) { */
    /*         ballDir.x = +1; */
    /*         ballDir.y = (Ball.position.y - PlayerB.position.y) / -90.f; */
    /*         racketRec.y = 1 * racketTexture.height / NUM_FRAMES; */
    /*     } else if (Ball.position.y >= GetScreenHeight() - (ballTexture.height / 2.f)) { */
    /*         ballDir.y *= -1; */
    /*     } else if (Ball.position.y <= 0 + (ballTexture.height / 2.f)) { */
    /*         ballDir.y *= -1; */
    /*     } */

    /*     if (Ball.position.x <= 0) { */
    /*         PlayerBScore++; */
    /*         bBallLaunched = false; */
    /*         Ball.position = (Vector2){(GetScreenWidth() / 2.f), (GetScreenHeight() / 2.f)};
     */
    /*         PlayerA.position = (Vector2){20.f, GetScreenHeight() / 2.f}; */
    /*         PlayerB.position = (Vector2){GetScreenWidth() - 20.f, GetScreenHeight() / 2.f};
     */
    /*         ballDir = (Vector2){1, 0}; */
    /*     } else if (Ball.position.x >= GetScreenWidth()) { */
    /*         PlayerAScore++; */
    /*         bBallLaunched = false; */
    /*         Ball.position = (Vector2){(GetScreenWidth() / 2.f), (GetScreenHeight() / 2.f)};
     */
    /*         PlayerA.position = (Vector2){20.f, GetScreenHeight() / 2.f}; */
    /*         PlayerB.position = (Vector2){GetScreenWidth() - 20.f, GetScreenHeight() / 2.f};
     */
    /*         ballDir = (Vector2){-1, 0}; */
    /*     } */
    /* } */

    /* sprintf(debugText, "%f", (Ball.position.y - PlayerA.position.y) / -90.f); */
    /* sprintf(playerAScoreStr, "%i", PlayerAScore); */
    /* sprintf(playerBScoreStr, "%i", PlayerBScore); */
}

int main(void) {
    // Initialization
    //-------------------------------------------------------------------------------------

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Pong");

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
