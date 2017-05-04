#include "Game_Header.hpp"

Tile::Tile()
{
    contentype=nuul;
}

void Tile::hideOut(point tileSize, point tilePos)
{
    xsize=tileSize.x;
    ysize=tileSize.y;
    lcorner=tilePos;
    pos.x=tilePos.x+xsize/2;
    pos.y=tilePos.y+ysize/2;
    alignClickArea();
}
