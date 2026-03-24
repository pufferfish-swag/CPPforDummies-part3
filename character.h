#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

//character inherit from base character
class Character : public BaseCharacter
{
public:
    //declare character.cpp
    Character(int winWidth, int winHeight);
    virtual void tick(float deltaTime) override;
    Vector2 getScreenPos(){ return screenPos; }
private:

};

#endif