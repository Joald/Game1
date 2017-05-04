#include "Game_Header.hpp"

bool stat::setValue(statVal nv)
{
    if(valSet)
        return 0;
    val=nv;
    valSet=1;
    return 1;
}

stat::stat(){
    this->setValue(bignumber);
    valSet=0;
}

statVal stat::getVal()
{
   return val+tempModifier+baseModifier;
}

bool stat::check(statVal src)
{
    return src<getVal();
}
stat::stat(statVal src)
{
    setValue(src);
    valSet=1;
}

