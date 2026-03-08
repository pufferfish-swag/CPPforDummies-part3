#include "raylib.h"
#include "raymath.h"
#include "character.h"

void draw_worldMap(Texture2D worldMap, Vector2 mapPos)
{

    const float rotationWorldMap{0.0};
    const float scaleWorldMap{4.0};

    DrawTextureEx(worldMap, mapPos, rotationWorldMap, scaleWorldMap, WHITE);
}


int main()
{
    const int WindowWidth{576};
    const int WindowHeight{576};

    // initialize window
    InitWindow(WindowWidth, WindowHeight, "Classy Clash - Winter Edition by Adjie Wahyudinata");

    Texture2D worldMap = LoadTexture("nature_tileset/WorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};

    character knight;
    knight.setScreenPos(WindowWidth, WindowHeight);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
        //move the map
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the world map
        draw_worldMap(worldMap, mapPos);

        //set player tick
        knight.tick(GetFrameTime());

        EndDrawing();
    }

    UnloadTexture(worldMap);

    CloseWindow();
}
