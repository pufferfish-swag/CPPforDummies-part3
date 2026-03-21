#include "character.h"
#include "raymath.h"

//this is called constructor
Character::Character(int winWidth, int winHeight){
    width = texture.width / maxFrames;
    height = texture.height;

    screenPos = {   static_cast<float>(winWidth) / 2.f - scale * (0.5f * width),
                    static_cast<float>(winHeight) / 2.f - scale * (0.5f * height)
    };
}

void Character::tick(float deltaTime)
{
    BaseCharacter::tick(deltaTime);

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
}