#include "character.h"
#include "raymath.h"

//this is called constructor
Character::Character(int winWidth, int winHeight) :
    windowHeight(winHeight),
    windowWidth(winWidth)
{
    width = texture.width / maxFrames;
    height = texture.height;
}

Vector2 Character::getScreenPos(){
    return Vector2{
        static_cast<float>(windowWidth) / 2.f - scale * (0.5f * width),
        static_cast<float>(windowHeight) / 2.f - scale * (0.5f * height)

    }
}

void Character::tick(float deltaTime)
{
    const float movMapSpeed{1.0};
    if (IsKeyDown(KEY_A))
        velocity.x -= movMapSpeed;
    if (IsKeyDown(KEY_D))
        velocity.x += movMapSpeed;
    if (IsKeyDown(KEY_W))
        velocity.y -= movMapSpeed;
    if (IsKeyDown(KEY_S))
        velocity.y += movMapSpeed;
    
    BaseCharacter::tick(deltaTime);
}