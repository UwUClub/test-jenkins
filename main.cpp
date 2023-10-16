#include "raylib.h"

int main(int argc, const char **argv) {
    // Initialization
    const int screenWidth = 1280;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "test");

    // NOTE: The following only works after calling InitWindow() (i.e,. RayLib is initialized)
    // create a texture from a path
    Texture2D texture = LoadTexture("em.png");
    // create a rect for the texture
    Rectangle sourceRec = {0.0f, 0.0f, (float) texture.width, (float) texture.height};
    // create a rect for the screen
    Rectangle destRec = {screenWidth / 2.0f, screenHeight / 2.0f, (float) texture.width, (float) texture.height};
    // create a vector for the origin
    Vector2 origin = {0.0f, 0.0f};

    SetTargetFPS(60);

    // Main loop
    while(!WindowShouldClose()) {

        // Update the display
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, WHITE);

        EndDrawing();
    }

    // Cleanup
    CloseWindow();

    return 0;
}