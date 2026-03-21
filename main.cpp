#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "prop.h"
#include "enemy.h"

void draw_worldMap(Texture2D worldMap, Vector2 mapPos)
{

    const float rotationWorldMap{0.0};
    const float scaleWorldMap{4.0};

    DrawTextureEx(worldMap, mapPos, rotationWorldMap, scaleWorldMap, WHITE);
}


int main()
{
    const int WindowWidth{480};
    const int WindowHeight{480};

    // initialize window
    InitWindow(WindowWidth, WindowHeight, "Classy Clash - Winter Edition by Adjie Wahyudinata");

    Texture2D worldMap = LoadTexture("nature_tileset/WorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    Character knight(WindowWidth, WindowHeight);
    
    //call member list from prop.h
    Prop props[2]{
        Prop{Vector2{600.f,300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{300.f,500.f}, LoadTexture("nature_tileset/Log.png")}
    };

    Enemy goblin{
        Vector2{},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };
    goblin.setTarget(&knight);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
        //move the map
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the world map
        draw_worldMap(worldMap, mapPos);

        // draw the props - why stephen didn't put the checkCollisionRec here?
        for(auto prop : props){
            prop.Render(knight.getWorldPos());
        }

        //set player tick movement
        knight.tick(GetFrameTime());
        //check map boundaries
        if( knight.getWorldPos().x < 0.f || 
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + WindowWidth > worldMap.width * mapScale ||
            knight.getWorldPos().y + WindowHeight > worldMap.height * mapScale)
            {  
                knight.undoMovement();  
            }
        //check prop collision
        for(auto prop : props){
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }
        //draw the enemy
        goblin.tick(GetFrameTime());

        EndDrawing();
    }
    
    UnloadTexture(worldMap);

    CloseWindow();
}
