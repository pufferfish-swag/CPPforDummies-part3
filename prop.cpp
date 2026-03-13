#include "prop.h"
#include "raymath.h"
//prop member initialize list
Prop::Prop(Vector2 pos, Texture2D tex):
    worldPos(pos),
    texture(tex)
{

}

void Prop::Render(Vector2 knightPos){
    Vector2 screenPos{ Vector2Subtract(worldPos, knightPos) };
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}