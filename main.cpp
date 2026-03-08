#include "raylib.h"
#include "raymath.h"

void draw_worldMap(Texture2D worldMap, Vector2 mapPos)
{

    const float rotationWorldMap{0.0};
    const float scaleWorldMap{4.0};

    DrawTextureEx(worldMap, mapPos, rotationWorldMap, scaleWorldMap, WHITE);
}

class character
{
public:
    Vector2 getWorldPos() { return worldPos; }
    void setScreenPos(int winWidth, int winHeight);
    void tick(float deltaTime);

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};
    // 1: facing right, -1: facing left
    float rightLeft{1.f};
    // anim variables
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f / 12.f};
    const float speed{4.f};
};

void character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {
        (float)winWidth / 2.f - 4.f * (0.5f * (float)texture.width / 6.0f),
        (float)winHeight / 2.f - 4.f * (0.5f * (float)texture.height)
    };
}

void character::tick(float deltaTime)
{
    Vector2 direction{};
    const float movMapSpeed{1.0};
    if (IsKeyDown(KEY_A))
        direction.x -= movMapSpeed;
    if (IsKeyDown(KEY_D))
        direction.x += movMapSpeed;
    if (IsKeyDown(KEY_W))
        direction.y -= movMapSpeed;
    if (IsKeyDown(KEY_S))
        direction.y += movMapSpeed;

    // checking player movement
    if (Vector2Length(direction) != 0.0)
    {
        // set worldPos = worldPos + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        // equivalent of `if else` statement
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        // set knight sd run if there's movement
        texture = run;
    }
    else
    {
        // set knight as idle
        texture = idle;
    }
    // update anim frame, shift + alt + f for formatting
    runningTime += deltaTime;
    if (runningTime > updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    Rectangle knightSource{frame * (float)texture.width / 6.0f, 0.0f, rightLeft * (float)texture.width / 6.0f, (float)texture.height};
    Rectangle knightDest{screenPos.x, screenPos.y, 6.0f * (float)texture.width / 6.0f, 6.0f * (float)texture.height};
    Vector2 knightOrigin{};
    DrawTexturePro(texture, knightSource, knightDest, knightOrigin, 0.0f, WHITE);
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
        knight.tick(GetFrameTime());

        EndDrawing();
    }

    UnloadTexture(worldMap);

    CloseWindow();
}
