#pragma once
#include "Game_Header.hpp"

class stat
{
    statVal val;
    statType type;
    statVal tempModifier;
    statVal baseModifier;
    bool valSet;
public:
    bool check(statVal);
    stat(statVal);
    stat();
    bool setValue(statVal);///do not use this for anything other than initialization
    statVal getVal();
    statVal getBaseVal();
    void modTempModifier(statVal);
    void modBaseModifier(statVal);
};
