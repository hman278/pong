/*******************************************************************************************
*
*   raylib [core] example - Basic 3d example
*
*   Welcome to raylib!
*
*   To compile example, just press F5.
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2020 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"

#define PHYSAC_IMPLEMENTATION
#include "physac.h"

struct Sprite {
    Texture2D Texture;
    Vector2 Position;
};

enum GAME_MODE {
    SP = 0,
    MP = 1
} gameMode;

enum MENU_MODE {
    MainMenu = 0,
    MenuNone = 1,
    GameMenu = 2
} menuMode;

static const char* const menuModeNames[3] =
{
    "Main Menu",
    "None",
    "Game Menu"
};

int main() 
{   
    // Initialization
    //-------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "networked ping with ai");

    InitPhysics();

    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 0.0f };
    camera.target = (Vector3){ 0.01f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 90.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    
    SetCameraMode(camera, CAMERA_CUSTOM);

    float spY = 200.f;
    float mpY = 50.f;
    float exitY = -100.f; 
    float gameMenuY = 0.f;
    float gameReturnY = 115.f;
    float gameExitY = -5.;

    float buttonRoundness = 0.2f; 
    float buttonWidth = 300.f;
    float buttonHeight = 110.f;

    float gameMenuRoundness = 0.1f;
    float gameMenuWidth = 500.f;
    float gameMenuHeight = 300.f;

    float ballSize = 20.f;

    float playerWidth = 20.f;
    float playerHeight = 100.f;

    float playerSpeed = 5.f;

    Vector2 mousePoint = { 0.0f, 0.0f };

    float player1Y = (GetScreenHeight() / 2.f) - (playerHeight / 2.f);
    float player2Y = (GetScreenHeight() / 2.f) - (playerHeight / 2.f);

    float xMultiplier = 1000.f;

    bool bBallLaunched = false;
    float ballX = 0.f;
    float ballY = 0.f;
    Vector2 ballRectPos = { 0, 0 };

    PhysicsBody ball = CreatePhysicsBodyRectangle((Vector2) {ballX, ballY}, ballSize, ballSize, 10);
    ball->useGravity = false;
    ball->enabled = true;
    ball->restitution = 0;
    ball->inertia = 0;

    // string that prints mouse coordinates on screen
    char *mousePosStr = (char*)malloc(100 * sizeof(char));
    char *menuModeStr = (char*)malloc(25 * sizeof(char));

    int p1Score = 0, p2Score = 0;
    char* p1ScoreStr = (char*)malloc(20 * sizeof(char));
    char* p2ScoreStr = (char*)malloc(20 * sizeof(char));

    bool player1Score = false;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);
        //----------------------------------------------------------------------------------

        UpdatePhysics();

        mousePoint = GetMousePosition();

        Color spButtonColor = GRAY;
        Color mpButtonColor = GRAY;
        Color exitButtonColor = GRAY;
        Color gameExitButtonColor = GRAY;
        Color gameReturnButtonColor = GRAY;

        ballRectPos = ball->position;

        sprintf(mousePosStr,"Mouse position: %fpx %fpx", mousePoint.x, mousePoint.y);      
        sprintf(menuModeStr, "Menu Mode: %s", menuModeNames[menuMode]);
        sprintf(p1ScoreStr, "P1 Score: %i", p1Score);
        sprintf(p2ScoreStr, "P2 Score: %i", p2Score);

        Rectangle spButton = { (GetScreenWidth() / 2.f) - (buttonWidth / 2.f), (GetScreenHeight() / 2.f) - spY, buttonWidth, buttonHeight };
        Rectangle mpButton = { (GetScreenWidth() / 2.f) - (buttonWidth / 2.f), (GetScreenHeight() / 2.f) - mpY, buttonWidth, buttonHeight };
        Rectangle exitButton = { (GetScreenWidth() / 2.f) - (buttonWidth / 2.f), (GetScreenHeight() / 2.f) - exitY, buttonWidth, buttonHeight };
        Rectangle gameMenuContainer = { (GetScreenWidth() / 2.f) - (gameMenuWidth / 2.f), (GetScreenHeight() / 2.0f) - (gameMenuHeight / 2.f), gameMenuWidth, gameMenuHeight };
        Rectangle gameReturnButton = { (GetScreenWidth() / 2.f) - (buttonWidth / 2.f), (GetScreenHeight() / 2.f) - gameReturnY, buttonWidth, buttonHeight };
        Rectangle gameExitButton = { (GetScreenWidth() / 2.f) - (buttonWidth / 2.f), (GetScreenHeight() / 2.f) - gameExitY, buttonWidth, buttonHeight };
        Rectangle ballRect = { ballRectPos.x, ballRectPos.y, ballSize, ballSize };

        Rectangle player1 = { +20.f, player1Y - playerHeight / 2.f, playerWidth, playerHeight };
        Rectangle player2 = { GetScreenWidth() - 40.f, player2Y - playerHeight / 2.f, playerWidth, playerHeight };
        
        if (!bBallLaunched)
        {
            ball->velocity = (Vector2) { 0, 0 };
            if (!player1Score)
            {
                ballX = player1.x + player1.width;
                ballY = player1Y + playerHeight/2.f - ballSize/2.f;
            }
            else
            {
                ballX = player2.x - player2.width;
                ballY = player2Y + playerHeight/2.f - ballSize/2.f;
            }
            
            ball->position.x = ballX;
            ball->position.y = ballY;
        }

        if (menuMode == MainMenu)
        {
            if (CheckCollisionPointRec(mousePoint, spButton))
            {
                spButtonColor = YELLOW; 

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    menuMode = MenuNone; 
                    gameMode = SP;
                } 
            }
            else if  (CheckCollisionPointRec(mousePoint, mpButton))
            {
                mpButtonColor = YELLOW;

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    menuMode = MenuNone; 
                    gameMode = MP;
                } 
            }
            else if  (CheckCollisionPointRec(mousePoint, exitButton))
            {
                exitButtonColor = YELLOW;

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
                {
                    menuMode = MenuNone;
                    CloseWindow();
                }
            }
        }
        else if (menuMode == GameMenu)
        {
            if (CheckCollisionPointRec(mousePoint, gameReturnButton))
            {
                gameReturnButtonColor = YELLOW;

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) menuMode = MenuNone;
            }
            else if  (CheckCollisionPointRec(mousePoint, gameExitButton))
            {
                gameExitButtonColor = YELLOW;

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
                {
                    p1Score = 0;
                    p2Score = 0;
                    player1Y = GetScreenHeight() / 2.f - playerHeight / 2.f;
                    player2Y = GetScreenHeight() / 2.f - playerHeight / 2.f;
                    bBallLaunched = false;
                    player1Score = false;
                    menuMode = MainMenu;
                }
            }
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            if (menuMode == MainMenu) 
            {
                // Menu buttons
                DrawRectangleRounded(spButton, buttonRoundness, 0, spButtonColor);
                DrawRectangleRounded(mpButton, buttonRoundness, 0, mpButtonColor);
                DrawRectangleRounded(exitButton, buttonRoundness, 0, exitButtonColor);

                DrawText("Singleplayer", (GetScreenWidth() / 2) - 90, (GetScreenHeight() / 2) - spY + (buttonHeight/2) - 15, 30, BLACK);
                DrawText("Multiplayer", (GetScreenWidth() / 2) - 80, (GetScreenHeight() / 2) - mpY + (buttonHeight/2) - 15, 30, BLACK);
                DrawText("Exit", (GetScreenWidth() / 2) - 30, (GetScreenHeight() / 2) - exitY + (buttonHeight/2) - 15, 30, BLACK);
            }
            else
            {
                // Middle line
                DrawRectangle((GetScreenWidth() - 10.f) / 2.0f, (GetScreenHeight() - 1000.f) / 2.0f, 10.f, 1000.f, GRAY);

                DrawText(p1ScoreStr, 10, 10, 20, DARKGRAY);
                DrawText(p2ScoreStr, 600, 10, 20, DARKGRAY);

                // Draw player rackets and the ball
                DrawRectangleRounded(player1, 0.f, 0, GREEN);
                DrawRectangleRounded(player2, 0.f, 0, RED);
                DrawRectangleRounded(ballRect, 0.f, 0, RED);

                // Player 1 movement
                if (IsKeyDown(KEY_W) && player1Y >= 5.f)
                {
                    player1Y -= playerSpeed;
                }
                else if (IsKeyDown(KEY_S) && player1Y <= GetScreenHeight() - playerHeight)
                {
                    player1Y += playerSpeed;
                }

                // calculate ball force
                float player1Pos = player1Y + (playerHeight / 2.f);
                float player2Pos = player2Y + (playerHeight / 2.f);
                float p1YMultiplier = (ball->position.y - player1Pos) * 10.f;
                float p2YMultiplier = (ball->position.y - player2Pos) * 10.f;

                if (IsKeyPressed(KEY_SPACE) && !bBallLaunched)
                {
                    bBallLaunched = true;

                    if (player1Score == false)
                    {
                        PhysicsAddForce(ball, (Vector2) { 1000, 0 });
                    }
                    else 
                    {
                        PhysicsAddForce(ball, (Vector2) { -1000, 0 });
                    }
                }

                if (CheckCollisionRecs(ballRect, player1))
                {
                    xMultiplier = 1000;
                    ball->velocity = (Vector2) { 0, 0 };
                    PhysicsAddForce(ball, (Vector2) { xMultiplier, p1YMultiplier });
                }
                else if (CheckCollisionRecs(ballRect, player2))
                {
                    xMultiplier = -1000;
                    ball->velocity = (Vector2) { 0, 0 };
                    PhysicsAddForce(ball, (Vector2) { xMultiplier, p2YMultiplier });
                }

                if (ball->position.y <= 0)
                {
                    ball->velocity = (Vector2) { 0, 0 };
                    PhysicsAddForce(ball, (Vector2) { xMultiplier, 500 });
                }
                else if (ball->position.y >= GetScreenHeight())
                {
                    ball->velocity = (Vector2) { 0, 0 };
                    PhysicsAddForce(ball, (Vector2) { xMultiplier, -500 });
                }

                if (ball->position.x <= 0)
                {
                    p2Score += 1;
                    bBallLaunched = false;
                    player1Score = false;
                }
                else if (ball->position.x >= GetScreenWidth())
                {
                    p1Score += 1;
                    bBallLaunched = false;
                    player1Score = true;
                }

                // Player 2 movement
                if (gameMode == MP)
                {
                    if (IsKeyDown(KEY_UP) && player2Y >= 5.f)
                    {
                        player2Y -= playerSpeed;
                    }
                    else if (IsKeyDown(KEY_DOWN) && player2Y <= GetScreenHeight() - playerHeight)
                    {
                        player2Y += playerSpeed;
                    }
                }
                else // SP 
                {
                    player2Y = Lerp(player2Y, ball->position.y, 0.1f);
                }

                if (menuMode == GameMenu)
                {
                    DrawRectangleRounded(gameMenuContainer, gameMenuRoundness, 0,  Fade(GRAY, 0.4f));
                    DrawRectangleRounded(gameReturnButton, gameMenuRoundness, 0,  gameReturnButtonColor);
                    DrawRectangleRounded(gameExitButton, gameMenuRoundness, 0,  gameExitButtonColor);

                    DrawText("Return", (GetScreenWidth() / 2) - 55, (GetScreenHeight() / 2) - gameReturnY + (buttonHeight/2) - 15, 30, BLACK);
                    DrawText("Exit", (GetScreenWidth() / 2) - 30, (GetScreenHeight() / 2) - gameExitY + (buttonHeight/2) - 15, 30, BLACK);
                }
                else if (menuMode == MenuNone)
                {
                    if (IsKeyPressed(KEY_P))
                    {
                        menuMode = GameMenu;
                    }
                }
            }

            DrawText(mousePosStr, 10, 30, 10, DARKGRAY);
            DrawText(menuModeStr, 10, 40, 10, DARKGRAY);
            DrawFPS(10, 420);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    DestroyPhysicsBody(ball);

    ClosePhysics();

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
