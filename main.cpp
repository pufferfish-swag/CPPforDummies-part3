#include "raylib.h"
#include "raymath.h"

void draw_worldMap(Texture2D worldMap, Vector2 mapPos){

    const float rotationWorldMap{0.0};
    const float scaleWorldMap{4.0};
    
    DrawTextureEx(worldMap, mapPos, rotationWorldMap, scaleWorldMap, WHITE);
}

class character
{
    public:
        Vector2 getWorldPos(){
            return worldPos;
        }
    private:
        Texture2D texture;
        Texture2D idle;
        Texture2D run;
        Vector2 screenPos;
        Vector2 worldPos;
        //1: facing right, -1: facing left
        float rightLeft{1.f};
        //anim variables
        float runningTime{};
        int frame{};
        const int maxFrames{6};
        const float updateTime{1.f/12.f}; 
};


int main(){
    
    const int WindowWidth{576};
    const int WindowHeight{576};

    //initialize window
    InitWindow(WindowWidth, WindowHeight, "Classy Clash - Winter Edition by Adjie Wahyudinata");
    
    Texture2D worldMap = LoadTexture("nature_tileset/WorldMap24x24.png");
    Vector2 mapPos{0.0,0.0};
    const float speed(5.0);

    //knight 
    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");
    //starting point anim for knight
    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    const float scale{6.0};
    const float divide{2.0};
    Vector2 knightPos
    {
        (float)WindowWidth/divide - scale * (0.5f * (float)knight.width/6.0f),
        (float)WindowHeight/divide - scale * (0.5f * (float)knight.height)
    };

    //1: facing right, -1: facing left
    float rightLeft{1.f};
    //anim variables
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f/12.f}; 
    
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
        
        //checking player movement
        if(Vector2Length(direction) != 0.0){
            //set mapPos = mapPos - direction
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
            //equivalent of `if else` statement 
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
            //set knight sd run if there's movement
            knight = knight_run; 
        }else{
            //set knight as idle
            knight = knight_idle;
        }

        //draw the world map
        draw_worldMap(worldMap, mapPos);

        //update anim frame
        runningTime += GetFrameTime();
        if (runningTime > updateTime){
            frame++;
            runningTime = 0.f;
            if (frame > maxFrames) frame = 0;
        }

        //draw character
        Rectangle knightSource{frame * (float)knight.width/6.0f, 0.0f, rightLeft * (float)knight.width/6.0f, (float)knight.height};
        Rectangle knightDest{knightPos.x, knightPos.y, 6.0f * (float)knight.width/6.0f, 6.0f * (float)knight.height};
        Vector2 knightOrigin{};
        DrawTexturePro(knight, knightSource, knightDest, knightOrigin, 0.0f, WHITE);

        EndDrawing();
    }
    
    UnloadTexture(worldMap);
    
    CloseWindow();
}
