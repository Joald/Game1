#pragma once
#include "Game_Header.hpp"
class GameClass;
class Fight
{
    public:
        bool isFighting;
        void Fightx(point,GameClass&);
        point leftCorner;
        point midle;
};
