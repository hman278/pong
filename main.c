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

#include "raylib.h"

enum MENU_MODE {
    MainMenu = 0,
    MenuNone = 1,
    GameMenu = 2
} menuMode;

int main() 
{   
    // Initialization
    //-------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "networked ping with ai");

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

    float buttonRoundness = 0.2f; 
    float buttonWidth = 300.f;
    float buttonHeight = 110.f;

    float gameMenuRoundness = 0.1f;
    float gameMenuWidth = 500.f;
    float gameMenuHeight = 200.f;

    Vector2 mousePoint = { 0.0f, 0.0f };

    // string that prints mouse coordinates on screen
    char *mousePosStr = (char*)malloc(100 * sizeof(char));

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);
        //----------------------------------------------------------------------------------

        mousePoint = GetMousePosition();

        Color spButtonColor = GRAY;
        Color mpButtonColor = GRAY;
        Color exitButtonColor = GRAY;

        sprintf(mousePosStr,"Mouse position: %fpx %fpx", mousePoint.x, mousePoint.y);

        Rectangle spButton = { (GetScreenWidth() / 2.f) - (buttonWidth / 2.f), (GetScreenHeight() / 2.f) - spY, buttonWidth, buttonHeight };
        Rectangle mpButton = { (GetScreenWidth() / 2.f) - (buttonWidth / 2.f), (GetScreenHeight() / 2.f) - mpY, buttonWidth, buttonHeight };
        Rectangle exitButton = { (GetScreenWidth() / 2.f) - (buttonWidth / 2.f), (GetScreenHeight() / 2.f) - exitY, buttonWidth, buttonHeight };
        Rectangle gameMenuContainer = { (GetScreenWidth() / 2.f) - (gameMenuWidth / 2.f), (GetScreenHeight() / 2.0f) - gameMenuY, gameMenuWidth, gameMenuHeight };

        if (menuMode == MainMenu)
        {
            if (CheckCollisionPointRec(mousePoint, spButton))
            {
                spButtonColor = YELLOW;

                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) menuMode = MenuNone;
            }
            else if  (CheckCollisionPointRec(mousePoint, mpButton))
            {
                mpButtonColor = YELLOW;

                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) menuMode = MenuNone;
            }
            else if  (CheckCollisionPointRec(mousePoint, exitButton))
            {
                exitButtonColor = YELLOW;

                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) menuMode = MenuNone;
            }
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE); 

            if (menuMode == MainMenu) 
            {
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

                DrawText("P1 Score: ", 10, 10, 20, DARKGRAY);
                DrawText("P2 Score: ", 600, 10, 20, DARKGRAY);

                if (menuMode == GameMenu)
                {
                    DrawRectangleRounded(gameMenuContainer, gameMenuRoundness, 0,  Fade(GRAY, 0.4f));
                }
                else if (menuMode == MenuNone)
                {
                    if (IsKeyPressed(KEY_P))
                    {
                        menuMode = GameMenu;
                    }
                }
            }
            
            DrawText(mousePosStr, 10, 10, 10, DARKGRAY);
            DrawFPS(10, 420);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}