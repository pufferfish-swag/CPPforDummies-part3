#include "raylib.h"
#include "raymath.h"

void draw_worldMap(Texture2D worldMap, Vector2 mapPos){

    const float rotationWorldMap{0.0};
    const float scaleWorldMap{4.0};
    
    DrawTextureEx(worldMap, mapPos, rotationWorldMap, scaleWorldMap, WHITE);
}

int main(){
    
    const int WindowWidth{576};
    const int WindowHeight{576};

    //initialize window
    InitWindow(WindowWidth, WindowHeight, "Classy Clash - Winter Edition by Adjie Wahyudinata");
    
    Texture2D worldMap = LoadTexture("nature_tileset/WorldMap24x24.png");
    Vector2 mapPos{0.0,0.0};
    const float speed(5.0);

    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    const float scale{6.0};
    const float divide{2.0};
    Vector2 knightPos{
        (float)WindowWidth/divide - scale * (0.5f * (float)knight.width/6.0f),
        (float)WindowHeight/divide - scale * (0.5f * (float)knight.height)
    };
    
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        
        //moving the map with direction
        Vector2 direction{};
        const float movMapSpeed{1.0};
        if(IsKeyDown(KEY_A)) direction.x -= movMapSpeed;
        if(IsKeyDown(KEY_D)) direction.x += movMapSpeed;
        if(IsKeyDown(KEY_W)) direction.y -= movMapSpeed;
        if(IsKeyDown(KEY_S)) direction.y += movMapSpeed;
        
        //checking when player reach the edge of the map
        if(Vector2Length(direction) != 0.0){
            //set mapPos = mapPos - direction
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
        }

        //draw the world map
        draw_worldMap(worldMap, mapPos);

        //draw character
        Rectangle knightSource{0.0f, 0.0f, (float)knight.width/6.0f, (float)knight.height};
        Rectangle knightDest{knightPos.x, knightPos.y, 6.0f * (float)knight.width/6.0f, 6.0f * (float)knight.height};
        Vector2 knightOrigin{};
        DrawTexturePro(knight, knightSource, knightDest, knightOrigin, 0.0f, WHITE);

        EndDrawing();
    }
    
    UnloadTexture(worldMap);
    
    CloseWindow();
}
