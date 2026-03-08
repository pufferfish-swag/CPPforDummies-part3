#include "character.h"
#include "raymath.h"

character::character(){
    width = texture.width / maxFrames;
    height = texture.height;
}

void character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {
        (float)winWidth / 2.f - 4.f * (0.5f * width),
        (float)winHeight / 2.f - 4.f * (0.5f * height)
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

    Rectangle knightSource{frame * width, 0.0f, rightLeft * width, height};
    Rectangle knightDest{screenPos.x, screenPos.y, 6.0f * width, 6.0f * height};
    Vector2 knightOrigin{};
    DrawTexturePro(texture, knightSource, knightDest, knightOrigin, 0.0f, WHITE);
}