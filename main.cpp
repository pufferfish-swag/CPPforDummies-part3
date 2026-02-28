#include "raylib.h"

void draw_worldMap(Texture2D worldMap){

    //well, i just wanna have a static one
    Vector2 bgWorldMap{0.0,0.0};

    const float rotationWorldMap{0.0};
    const float scaleWorldMap{4.0};
    
    DrawTextureEx(worldMap, bgWorldMap, rotationWorldMap, scaleWorldMap, WHITE);
}

int main(){
    
    const int WindowWidth{576};
    const int WindowHeight{576};

    //initialize window
    InitWindow(WindowWidth, WindowHeight, "Classy Clash - Winter Edition by Adjie Wahyudinata");
    
    Texture2D worldMap = LoadTexture("nature_tileset/WorldMap24x24.png");
    
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        
        //Well, draw the world map obviously
        draw_worldMap(worldMap);

        EndDrawing();
    }
    
    UnloadTexture(worldMap);
    
    CloseWindow();
}
