#pragma once
#include "Game_Header.hpp"
class NPC;

class Level
{
public:
    Level(int,int);
    Level();
    std::string name;
    Shape border;
    std::vector<Shape> clutter;
    point playerEntryPoint;
    bool importFromFile(std::string,GameClass&);
    int width,height;
    std::vector<NPC/*std::vector<NPC>,*/>moblist;
    bool blocks(point);
    point getSafeMoveLocation(point,point);
};
