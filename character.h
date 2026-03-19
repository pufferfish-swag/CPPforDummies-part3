#include "raylib.h"
#include "BaseCharacter.h"

//character inherit from base character
class Character : public BaseCharacter
{
public:
    //declare character.cpp
    Character(int winWidth, int winHeight);
    void tick(float deltaTime);
private:

};