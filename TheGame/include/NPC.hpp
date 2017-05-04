#pragma once
#include "Game_Header.hpp"
class NPC : public ClickableEntity
{
    public:
    NPC();
    NPC(point);
    std::string name;
    ///vector<item>inventory; -> to be implemented along with items
    int health;
    int radius;
    mutable behaviourType behaviour;
    double speed;
    bool following;
    bool loadNPCFromFile(std::string); ///
    void translateTo(point);
};
///to be expanded
