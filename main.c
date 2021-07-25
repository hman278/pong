/*******************************************************************************************
*
*   Copyright (c) 2021 @hman278
*
********************************************************************************************/

#include "math.h"
#include "raylib.h"
#include "raymath.h"

// Define the number of frames for our racket sprite
#define NUM_FRAMES 2

typedef struct {
    Texture2D texture;
    Vector2 position;
} Sprite;

Sprite PlayerA, PlayerB, Ball;
Texture2D racketTexture;
Texture2D ballTexture;
Rectangle racketRec, ballRec;

bool bBallLaunched = false;

const float racketSpeed = 5.f;
const float ballSpeed = 5.f;

int PlayerAScore = 0;
int PlayerBScore = 0;

Vector2 ballDir = { 1, 0 };

char* debugText;
char* playerAScoreStr;
char* playerBScoreStr;

void Start()
{
    racketTexture = LoadTexture("resources/racket.png"); 
    ballTexture = LoadTexture("resources/ball.png");
    
    PlayerA.texture = racketTexture;
    PlayerB.texture = racketTexture;

    Ball.texture = ballTexture;

    racketRec = (Rectangle) { 0, 0, (float) racketTexture.width, (float) racketTexture.height / NUM_FRAMES };
    ballRec = (Rectangle) { 0, 0, (float) ballTexture.width, (float) ballTexture.height };

    // Set the initial player position
    PlayerA.position =  (Vector2) { 20.f, GetScreenHeight()/2.f };
    PlayerB.position = (Vector2) { GetScreenWidth() - 20.f, GetScreenHeight()/2.f };
    Ball.position = (Vector2) { (GetScreenWidth() / 2.f), (GetScreenHeight() / 2.f) };

    debugText = (char*)malloc(sizeof(char) * 100);
    playerAScoreStr = (char*)malloc(sizeof(char) * 100);
    playerBScoreStr = (char*)malloc(sizeof(char) * 100);
}

// draws texture on screen centered
void DrawTextureOnScreen(Texture2D texture, Rectangle source, Vector2 position, float frameCount, Color color)
{
    DrawTextureRec(texture, source, (Vector2) { position.x - texture.width / 2.f, position.y - texture.height / 2.f / frameCount }, color);
}

void Update()
{
   if (IsKeyDown(KEY_W) && PlayerA.position.y >= racketTexture.height / 2.f / NUM_FRAMES)
   {    
       PlayerA.position.y -= racketSpeed;
   }
   else if (IsKeyDown(KEY_S) && PlayerA.position.y <= GetScreenHeight() - racketTexture.height / 2.f / NUM_FRAMES)
   {
       PlayerA.position.y += racketSpeed;
   }

   if (IsKeyDown(KEY_UP) && PlayerB.position.y >= racketTexture.height / 2.f / NUM_FRAMES)
   {    
       PlayerB.position.y -= racketSpeed;
   }
   else if (IsKeyDown(KEY_DOWN) && PlayerB.position.y <= GetScreenHeight() - racketTexture.height / 2.f / NUM_FRAMES)
   {
       PlayerB.position.y += racketSpeed;
   }

   if (IsKeyPressed(KEY_SPACE))
   {
       bBallLaunched = true;
   }

    if (bBallLaunched)
    {
        Ball.position.x -= ballDir.x * ballSpeed;
        Ball.position.y -= ballDir.y * ballSpeed;
        racketRec.y = 0;

        // TODO: calculate y direction
        if (CheckCollisionRecs((Rectangle) {Ball.position.x, Ball.position.y, ballRec.width, ballRec.height}
        , (Rectangle) {PlayerA.position.x + (racketRec.width / 2.f), PlayerA.position.y - (racketRec.height / 2.f), racketRec.width, racketRec.height}))
        {
            ballDir.x = -1;
            // lower -90 to make the ball more bouncy
            ballDir.y = (Ball.position.y - PlayerA.position.y) / -90.f;
            racketRec.y = 1 * racketTexture.height / NUM_FRAMES;
        }
        else if (CheckCollisionRecs((Rectangle) {Ball.position.x, Ball.position.y, ballRec.width, ballRec.height}
        , (Rectangle) {PlayerB.position.x - (racketRec.width / 2.f), PlayerB.position.y - (racketRec.height / 2.f), racketRec.width, racketRec.height}))
        {
            ballDir.x = +1;
            ballDir.y = (Ball.position.y - PlayerB.position.y) / -90.f;
            racketRec.y = 1 * racketTexture.height / NUM_FRAMES;
        }
        else if (Ball.position.y >= GetScreenHeight() - (ballTexture.height / 2.f))
        { 
            ballDir.y *= -1;
        }
        else if (Ball.position.y <= 0 + (ballTexture.height / 2.f))
        {
            ballDir.y *= -1;
        }

        if (Ball.position.x <= 0)
        {
            PlayerBScore++;
            bBallLaunched = false;
            Ball.position = (Vector2) { (GetScreenWidth() / 2.f), (GetScreenHeight() / 2.f) };
            PlayerA.position =  (Vector2) { 20.f, GetScreenHeight()/2.f };
            PlayerB.position = (Vector2) { GetScreenWidth() - 20.f, GetScreenHeight()/2.f };
            ballDir = (Vector2) { 1, 0 };
        }
        else if (Ball.position.x >= GetScreenWidth())
        {
            PlayerAScore++;
            bBallLaunched = false;
            Ball.position = (Vector2) { (GetScreenWidth() / 2.f), (GetScreenHeight() / 2.f) };
            PlayerA.position =  (Vector2) { 20.f, GetScreenHeight()/2.f };
            PlayerB.position = (Vector2) { GetScreenWidth() - 20.f, GetScreenHeight()/2.f };
            ballDir = (Vector2) { -1, 0 };
        }
    }

    sprintf(debugText, "%f", (Ball.position.y - PlayerA.position.y) / -90.f);
    sprintf(playerAScoreStr, "%i", PlayerAScore);
    sprintf(playerBScoreStr, "%i", PlayerBScore);
}

int main() 
{   
    // Initialization
    //-------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib Pong");

    SetTargetFPS(120);               // Set our game to run at 120 frames-per-second
    //--------------------------------------------------------------------------------------

    Start();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        Update();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTextureOnScreen(racketTexture, racketRec, PlayerA.position, NUM_FRAMES, WHITE);
            DrawTextureOnScreen(racketTexture, racketRec, PlayerB.position, NUM_FRAMES, WHITE);
            DrawTextureOnScreen(ballTexture, ballRec, Ball.position, 1, WHITE);

            DrawFPS(10, 420);

            DrawText(playerAScoreStr, 10, 10, 30, BLUE);
            DrawText(playerBScoreStr, 740, 10, 30, BLUE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
