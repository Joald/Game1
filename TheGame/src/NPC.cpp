#include "Game_Header.hpp"
NPC::NPC()
{
    following=false;
    name="placeholder";
}

NPC::NPC(point t)
{
    following=false;
    name="placeholder";
    translateTo(t);
}

bool NPC::loadNPCFromFile(std::string fileName)
{
    std::ifstream inputStream;
    fileName+=".npc";
    alignClickArea();
    inputStream.open(fileName.c_str());
    if(!inputStream.is_open())
        return false;
    std::getline(inputStream,this->name);
    inputStream>>health;
    inputStream>>following;
    int behaviourint;
    inputStream>>behaviourint;
    switch(behaviourint)
    {
    case 1:
        behaviour=passive;
        break;
    case 2:
        behaviour=aggresive;
        break;
    case 3:
        behaviour=friendly;
        break;
    default:
        behaviour=passive;
        break;
    }
    return 1;
}
void NPC::translateTo(point t)
{
    pos=t;
    point alignment(t.x-xsize/2,t.y-ysize/2);
    lcorner=alignment;
    if(clickAreaAligned)
        clickArea.translateTo(alignment);
    else
    {
        alignClickArea();
        clickArea.translateTo(alignment);
    }
    sprite.setPosition(pointToVector(alignment));//pos.x-xsize/2,pos.y-ysize*8/10

}

