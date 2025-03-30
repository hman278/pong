/*******************************************************************************************
 *
 *   Copyright (c) 2025 @hman278
 *
 ********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "include/ball.h"
#include "include/game_assets.h"
#include "include/player_racket.h"
#include "raylib.h"
#include "raymath.h"

typedef enum { MENU, PAUSED, WAITING, ONGOING } GameState;

/* Globals */
GameState g_game_state;

PlayerRacket *g_player_a, g_player_b;
Ball* g_ball;

int g_player_a_score, g_player_b_score;

char* g_debug_text;

/* TODO: Make the ball go to the serving player */
void reset_positions() {
    player_set_position(g_player_a, PLAYER_A_START_POS);
    player_set_position(g_player_b, PLAYER_B_START_POS);
}

/* Set initial values */
void init() {
    load_game_assets();
    player_set_racket_texture(g_player_a, g_assets.racket_texture);
    player_set_racket_texture(g_player_b, g_assets.racket_texture);

    g_ball.base.texture = g_ball_texture;

    Rectangle racket_rec = (Rectangle){0, 0, (float)g_racket_texture.width,
                                       (float)g_racket_texture.height / g_player_a.frame_count};
    Rectangle ball_rec =
        (Rectangle){0, 0, (float)g_ball_texture.width, (float)g_ball_texture.height};

    g_player_a.rect = g_player_b.rect = racket_rec;
    g_ball.rect = ball_rec;

    reset_positions();
}

void shutdown() { unload_game_assets(); }

void update() {
    Vector2 player_a_move_dir = (Vector2){(int)IsKeyDown(KEY_W), (int)IsKeyDown(KEY_S)};
    Vector2 player_b_move_dir = (Vector2){(int)IsKeyDown(KEY_UP), (int)IsKeyDown(KEY_DOWN)};

    player_move(g_player_a, player_a_move_dir);
    player_move(g_player_b, player_b_move_dir);

    if (IsKeyPressed(KEY_SPACE)) {
        g_game_state = ONGOING;
    }

    /* Don't move the ball until someone serves it */
    if (g_game_state == ONGOING) {
        /* TODO: Hardcoded value, change to match current player */
        ball_move((Vector2){0, 1});

        // TODO: calculate y direction
        if (CheckCollisionRecs(
                (Rectangle){Ball.position.x, Ball.position.y, ballRec.width, ballRec.height},
                (Rectangle){PlayerA.position.x + (racketRec.width / 2.f),
                            PlayerA.position.y - (racketRec.height / 2.f), racketRec.width,
                            racketRec.height})) {
            ballDir.x = -1;
            // lower -90 to make the ball more bouncy
            ballDir.y = (Ball.position.y - PlayerA.position.y) / -90.f;
            racketRec.y = 1 * racketTexture.height / NUM_FRAMES;
        } else if (CheckCollisionRecs(
                       (Rectangle){Ball.position.x, Ball.position.y, ballRec.width, ballRec.height},
                       (Rectangle){PlayerB.position.x - (racketRec.width / 2.f),
                                   PlayerB.position.y - (racketRec.height / 2.f), racketRec.width,
                                   racketRec.height})) {
            ballDir.x = +1;
            ballDir.y = (Ball.position.y - PlayerB.position.y) / -90.f;
            racketRec.y = 1 * racketTexture.height / NUM_FRAMES;
        } else if (Ball.position.y >= GetScreenHeight() - (ballTexture.height / 2.f)) {
            ballDir.y *= -1;
        } else if (Ball.position.y <= 0 + (ballTexture.height / 2.f)) {
            ballDir.y *= -1;
        }

        if (Ball.position.x <= 0) {
            PlayerBScore++;
            bBallLaunched = false;
            Ball.position = (Vector2){(GetScreenWidth() / 2.f), (GetScreenHeight() / 2.f)};
            PlayerA.position = (Vector2){20.f, GetScreenHeight() / 2.f};
            PlayerB.position = (Vector2){GetScreenWidth() - 20.f, GetScreenHeight() / 2.f};
            ballDir = (Vector2){1, 0};
        } else if (Ball.position.x >= GetScreenWidth()) {
            PlayerAScore++;
            bBallLaunched = false;
            Ball.position = (Vector2){(GetScreenWidth() / 2.f), (GetScreenHeight() / 2.f)};
            PlayerA.position = (Vector2){20.f, GetScreenHeight() / 2.f};
            PlayerB.position = (Vector2){GetScreenWidth() - 20.f, GetScreenHeight() / 2.f};
            ballDir = (Vector2){-1, 0};
        }
    }

    sprintf(debugText, "%f", (Ball.position.y - PlayerA.position.y) / -90.f);
    sprintf(playerAScoreStr, "%i", PlayerAScore);
    sprintf(playerBScoreStr, "%i", PlayerBScore);
}

/* Draws texture on screen centered */
void draw_texture_on_screen(Texture2D texture, Rectangle source, Vector2 position,
                            float frame_count, Color color) {
    DrawTextureRec(texture, source,
                   (Vector2){position.x - texture.width / 2.f,
                             position.y - texture.height / 2.f / frame_count},
                   color);
}

int main() {
    // Initialization
    //-------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib Pong");

    SetTargetFPS(120);  // Set our game to run at 120 frames-per-second
    //--------------------------------------------------------------------------------------

    Start();

    // Main game loop
    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        // Update
        update();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        draw_texture_on_screen(racketTexture, racketRec, PlayerA.position, NUM_FRAMES, WHITE);
        draw_texture_on_screen(racketTexture, racketRec, PlayerB.position, NUM_FRAMES, WHITE);
        draw_texture_on_screen(ballTexture, ballRec, Ball.position, 1, WHITE);

        DrawFPS(10, 420);

        DrawText(playerAScoreStr, 10, 10, 30, BLUE);
        DrawText(playerBScoreStr, 740, 10, 30, BLUE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
