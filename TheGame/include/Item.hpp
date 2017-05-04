#pragma once
#include "Game_Header.hpp"

//class ClickableEntity;

class Item
{
public:
    std::vector<int> effect;///A number of an effect is this vector's index
    std::string name;
    itemType type;
    Item();
    bool loadItemFromFile(std::string);
    void addEffectToItem(int,int);///First goes a number of an effect, next it's value
};
