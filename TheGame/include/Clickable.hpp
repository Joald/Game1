#pragma once
#include "Game_Header.hpp"
class GameClass;
class Clickable
{
    public:
    Clickable(Rectangle);
    Clickable();
    void setClickArea(Rectangle);
    Rectangle clickArea;
    virtual bool isClicked(point, void(*func)(GameClass&),GameClass&gra)const;
    virtual bool isClicked(point, GameClass&gra)const;
    virtual void translateTo(point);
};
