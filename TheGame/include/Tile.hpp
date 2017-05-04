#pragma once
#include "Game_Header.hpp"

class Tile:public ClickableEntity
{
public:
    Tile();
    contentsType contentype;
    Entity cos;
    void hideOut(point,point);
};
